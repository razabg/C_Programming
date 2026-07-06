#include <linux/spinlock.h>

// Declare and initialize a spinlock statically
static DEFINE_SPINLOCK(my_lock);

// Shared resource protected by the lock
static int shared_counter = 0;

void increment_counter(void)
{
    unsigned long flags;

    // Acquire the lock (also disables interrupts on this CPU,
    // and saves their previous state into 'flags')
    spin_lock_irqsave(&my_lock, flags);

    // ---- critical section ----
    shared_counter++;
    // ---------------------------

    // Release the lock and restore interrupts to previous state
    spin_unlock_irqrestore(&my_lock, flags);
}