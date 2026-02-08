*This project has been created as part of the 42 curriculum by joesanto*

# Codexion

## Description

Codexion is a multi-threaded simulation inspired by the Dining Philosophers Problem. It models a team of coders competing for shared resources (dongles) to complete their work cycles.

**Goal:** Implement thread synchronization mechanisms to prevent deadlocks, race conditions, and starvation while supporting multiple scheduling policies.

**Overview:** Each coder must acquire two adjacent dongles to compile their code. The simulation tests different scheduling strategies (FIFO and EDF) to manage resource contention and prevent coder burnout.

---

## Instructions

### Compilation

**Standard build** (supports up to 200 coders):
```bash
make
```

**Custom maximum coders:**
```bash
make MAX_CODERS=100
```
Valid range: 0 to INT32_MAX

### Execution
```bash
./codexion <num_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <num_compiles> <dongle_cooldown> <scheduler>
```

**Parameters (all times in milliseconds):**
- `num_coders` - Number of coder threads
- `time_to_burnout` - Maximum time before burnout
- `time_to_compile` - Compilation duration
- `time_to_debug` - Debug duration
- `time_to_refactor` - Refactor duration
- `num_compiles` - Required compilations to complete
- `dongle_cooldown` - Cooldown after dongle release
- `scheduler` - `fifo` or `edf`

**Example:**
```bash
./codexion 9 1000 200 100 100 5 100 fifo
```

### Output Format

Each log message follows this structure:
```
<timestamp_ms> <coder_id> <event>
```

**Events:**
- `has taken a dongle` - Acquired one dongle (printed twice per compilation)
- `is compiling` - Started compilation phase
- `is debugging` - Started debugging phase
- `is refactoring` - Started refactoring phase
- `burned out` - Exceeded deadline and terminated

**Example output:**

<img width="1480" height="905" alt="codexion" src="https://github.com/user-attachments/assets/7288cbff-09e8-4112-8b98-036913158880" />

**Help:**
```bash
./codexion --help
```

---

## How It Works

### Coder Workflow

Each coder thread executes this cycle:

1. **Request dongles** - Join waiting queue for two adjacent dongles
2. **Compile** - Once acquired, reset deadline and compile
3. **Release dongles** - Return resources to pool
4. **Debug** - Execute debug phase
5. **Refactor** - Execute refactor phase
6. **Repeat** - Continue until burnout or simulation ends

A coder burns out if their deadline expires during any phase.

### Scheduling Policies

**FIFO (First In, First Out):**
- Coders join the end of each dongle's queue
- Priority based on request order
- Risk: Starvation if a coder's deadline arrives before their turn

**EDF (Earliest Deadline First):**
- Coders inserted by deadline proximity (sorted queue)
- Priority given to coders closest to burnout
- Prevents starvation by prioritizing urgent requests

### Queue Mechanism

When requesting dongles:
1. Coder enters the queue for both adjacent dongles (left and right)
2. Waits until first in line for both queues simultaneously
3. Marks dongles as in-use and dequeues itself
4. Proceeds to compilation

### Monitor Thread

Continuously checks:
- If any coder burned out → stop simulation, log result
- If required compilations reached → stop simulation

---

## Blocking Cases Handled

### Deadlock Prevention

**Problem:** Circular dependency if all coders lock dongles in the same order (left→right).

**Solution - Lock by Address Order:**
- Lock dongles based on memory address, not position
- Most coders: left→right (left has lower address)
- Last coder: right→left (right wraps to first dongle, lower address)
- Breaks circular wait (Coffman's fourth condition)

### Starvation Prevention

**FIFO Scheduler:**
- Inherent starvation risk when deadlines vary
- Demonstrates problem for comparison with EDF

**EDF Scheduler:**
- Deadline-based priority prevents starvation
- Coders closest to burnout always get priority

### Cooldown Handling

Before compiling, coders wait until current time exceeds the dongle's cooldown end time. This prevents immediate re-acquisition and simulates resource recovery.

### Precise Burnout Detection

A dedicated monitor thread continuously checks all coder deadlines independently from their work routines. This ensures burnout is detected immediately when a deadline expires, not just between phases.

### Log Serialization

All event logging (compilation start/end, burnout, etc.) is protected by a dedicated mutex. This prevents interleaved or corrupted output when multiple threads log simultaneously.

---

## Thread Synchronization Mechanisms

### Primitives Used

**`pthread_mutex_t`:**
- Dongle access control (one mutex per dongle)
- Queue modification protection
- Simulation state changes
- Log output serialization

**`pthread_cond_t`:**
- Signal dongle availability to waiting coders
- Notify state changes

### Shared Resource Coordination

**Dongle Access:**
```c
pthread_mutex_lock(&left_dongle->mutex);
pthread_mutex_lock(&right_dongle->mutex);
// Critical section: both dongles acquired
pthread_mutex_unlock(&right_dongle->mutex);
pthread_mutex_unlock(&left_dongle->mutex);
```

**Queue Operations:**
- Mutex protects enqueue/dequeue operations
- Condition variable signals when coder becomes queue head
- Race conditions prevented by atomic check-and-set under mutex

**Monitor State:**
- Mutex protects shared simulation state (RUNNING/STOPPED)
- Broadcasts simulation termination to all threads

**Logging:**
- Single global mutex serializes all output
- Prevents message interleaving from concurrent threads

### Race Condition Prevention Examples

**Dongle Acquisition:**
- Check dongle availability under same mutex
- Prevents time-of-check-to-time-of-use (TOCTOU) race

**Burnout Detection:**
- Deadline checks protected by coder state mutex
- Monitor and coder threads coordinate through shared lock

**Simulation Stop:**
- State transition (RUNNING→STOPPED) atomic under mutex
- All threads check state consistently before proceeding

---

## Resources

**Classic References:**
- [Dining Philosophers Problem Guide](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2) - Concurrency problem overview
- [Threading Fundamentals](https://youtu.be/0sVGnxg6Z3k?si=3CKEkPrFnZHnR23F) - POSIX threads tutorial

**AI Usage:**
AI assisted with project organization and code structure planning

---

## Author

**joesanto** - [42 School Porto]

---

## License

This project is part of the 42 School curriculum.
