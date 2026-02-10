*This project has been created as part of the 42 curriculum by joesanto*

# Codexion

## Description

Codexion is a multi-threaded simulation inspired by the Dining Philosophers Problem. It models a team of coders competing for shared resources (dongles) to complete their work cycles.

**Goal:** Implement thread synchronization mechanisms to prevent deadlocks, race conditions, and starvation while supporting multiple scheduling policies.

**Overview:** Each coder must acquire two adjacent dongles to compile their code. The simulation tests different scheduling strategies (FIFO and EDF) to manage resource contention and prevent coder burnout.

---

## Instructions

### Compilation

**Standard build:**
```bash
make
```
Defaults: `MAX_CODERS=200`, `START_PATTERN=ODD_EVEN`, `START_INTERVAL_MS=1`, `DEADLINE_START=CODER_START`

**Custom configuration:**
```bash
make MAX_CODERS=100 START_PATTERN=SEQUENTIAL DEADLINE_START=PROGRAM_START
```

**Build Parameters:**

- `MAX_CODERS` - Maximum number of coders supported (0 to INT32_MAX)
- `START_PATTERN` - Coder initialization strategy:
  - `SEQUENTIAL` - All coders start one after another
  - `ODD_EVEN` - Odd coders start first, even coders after `START_INTERVAL_MS` delay
  - Custom patterns for n-group staggered starts
- `START_INTERVAL_MS` - Delay between coder group starts (milliseconds)
- `DEADLINE_START` - When coder deadlines begin:
  - `PROGRAM_START` - All coders share same initial deadline from program start
  - `CODER_START` - Each coder's deadline starts when their routine begins

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

**Help:**
```bash
./codexion --help
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


---<img width="1666" height="900" alt="codexion" src="https://github.com/user-attachments/assets/cbd950e1-cb2b-4cdd-80b5-0d0d34720b94" />


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

**Lock Ordering Strategy:**

Dongles are locked by memory address rather than position to break circular dependencies:
- Most coders: lock left→right (left has lower memory address)
- Last coder: lock right→left (right wraps to first dongle with lower address)
- Breaks circular wait condition (Coffman's 4th condition)

**Odd-Even Start Pattern:**

When `START_PATTERN=ODD_EVEN`:
- Odd-numbered coders start their routines first
- Even-numbered coders start after `START_INTERVAL_MS` delay
- Prevents simultaneous neighbor dongle disputes at initialization
- Allows more coders to compile concurrently
- Reduces early starvation risk

### Starvation Prevention

**FIFO Scheduler:**
- Inherent starvation risk when deadlines vary
- Demonstrates problem for comparison with EDF

**EDF Scheduler:**
- Deadline-based priority prevents starvation
- Coders closest to burnout always get priority

**Start Pattern Impact:**
- `ODD_EVEN` pattern reduces initial resource contention
- Staggered starts give coders time to establish workflow before competition

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
- Broadcast simulation termination to all threads

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
- Condition variable broadcasts stop signal to all waiting threads
- Ensures consistent termination across all threads

**Logging:**
- Single global mutex serializes all output
- Prevents message interleaving from concurrent threads

### Race Condition Prevention Examples

**Dongle Acquisition:**
- Dongle availability checked under mutex lock
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

AI assisted with project organization and code structure planning.

---

## Author

**joesanto** - [42 School Porto]

---

## License

This project is part of the 42 School curriculum.
