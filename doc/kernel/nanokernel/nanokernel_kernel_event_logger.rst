.. _nanokernel_event_logger:

Kernel Event Logger
###################

Definition
**********

The kernel event logger is a standardized mechanism to record events within the Kernel while
providing a single interface for the user to collect the data. This mechanism is currently used
to log the following events:

* Sleep events (entering and exiting low power conditions).
* Context switch events.
* Interrupt events.

Kernel Event Logger Configuration
*********************************

Kconfig provides the ability to enable and disable the collection of events and to configure the
size of the buffer used by the event logger.

These options can be found in the following path :file:`kernel/Kconfig`.

General kernel event logger configuration:

* :option:`KERNEL_EVENT_LOGGER_BUFFER_SIZE`

  Default size: 128 words, 32-bit length.

Profiling points configuration:

* :option:`KERNEL_EVENT_INTERRUPT`

  Enables recording of interrupt-driven events by providing timestamp information.

* :option:`KERNEL_EVENT_SLEEP`

  Enables recording of sleep events:

    * Timestamp when the CPU went to sleep mode.
    * Timestamp when the CPU woke up.
    * The interrupt Id that woke the CPU up.

* :option:`KERNEL_EVENT_CONTEXT`

  Enables recording of context-switching events. Details include:

    * Which thread is leaving the CPU.
    * Timestamp when the event has occurred.

* :option:`KERNEL_EVENT_LOGGER_DYNAMIC`

  Allows modifying at runtime the events to record. At boot no event is recorded if enabled
  This flag adds functions allowing to enable/disable recoding of kernel event logger and
  task monitor events.

* :option:`KERNEL_EVENT_LOGGER_CUSTOM_TIMESTAMP`

  Enables the possibility to set the timer function to be used to populate kernel event logger
  timestamp. This has to be done at runtime by calling sys_k_event_logger_set_timer and providing
  the function callback.

Adding a Kernel Event Logging Point
***********************************

Custom trace points can be added with the following API:

* :c:func:`sys_k_event_logger_put()`

  Adds the profile of a new event with custom data.

* :cpp:func:`sys_k_event_logger_put_timed()`

  Adds timestamped profile of a new event.

.. important::

   The data must be in 32-bit sized blocks.

Retrieving Kernel Event Data
****************************

Applications are required to implement a fiber for accessing the recorded event messages
in both the nanokernel and microkernel systems. Developers can use the provided API to
retrieve the data, or may write their own routines using the ring buffer provided by the
event logger.

The API functions provided are:

* :c:func:`sys_k_event_logger_get()`
* :c:func:`sys_k_event_logger_get_wait()`
* :c:func:`sys_k_event_logger_get_wait_timeout()`

The above functions specify various ways to retrieve a event message and to copy it to
the provided buffer. When the buffer size is smaller than the message, the function will
return an error. All three functions retrieve messages via a FIFO method. The :literal:`wait`
and :literal:`wait_timeout` functions allow the caller to pend until a new message is
logged, or until the timeout expires.

Enabling/disabling event recording
**********************************

If KERNEL_EVENT_LOGGER_DYNAMIC is enabled, following functions must be checked for
dynamically enabling/disabling event recording at runtime:

* :cpp:func:`sys_k_event_logger_set_mask()`
* :cpp:func:`sys_k_event_logger_get_mask()`
* :cpp:func:`sys_k_event_logger_set_monitor_mask()`
* :cpp:func:`sys_k_event_logger_get_monitor_mask()`

Each mask bit corresponds to the corresponding event ID (mask is starting at bit 1 not bit 0).

More details are provided in function description.

Timestamp
*********

The timestamp used by the kernel event logger is 32-bit LSB of platform HW timer (for example
Lakemont APIC timer for Quark SE). This timer period is very small and leads to timestamp
wraparound happening quite often (e.g. every 134s for Quark SE).

see :option:`SYS_CLOCK_HW_CYCLES_PER_SEC`

This wraparound must be considered when analyzing kernel event logger data and care must be
taken when tickless idle is enabled and sleep duration can exceed maximum HW timer value.

Timestamp used by the kernel event logger can be customized by enabling following option:
:option:`KERNEL_EVENT_LOGGER_CUSTOM_TIMESTAMP`

In case this option is enabled, a callback function returning a 32-bit timestamp must
be provided to the kernel event logger by calling the following function at runtime:
:cpp:func:`sys_k_event_logger_set_timer()`

Message Formats
***************

Interrupt-driven Event Messaging
--------------------------------

The data of the interrupt-driven event message comes in two block of 32 bits:

* The first block contains the timestamp occurrence of the interrupt event.
* The second block contains the Id of the interrupt.

Example:

.. code-block:: c

   uint32_t data[2];
   data[0] = timestamp_event;
   data[1] = interrupt_id;

Context-switch Event Messaging
------------------------------

The data of the context-switch event message comes in two block of 32 bits:

* The first block contains the timestamp occurrence of the context-switch event.
* The second block contains the thread id of the context involved.

Example:

.. code-block:: c

   uint32_t data[2];
   data[0] = timestamp_event;
   data[1] = context_id;

Sleep Event Messaging
---------------------

The data of the sleep event message comes in three block of 32 bits:

* The first block contains the timestamp when the CPU went to sleep mode.
* The second block contains the timestamp when the CPU woke up.
* The third block contains the interrupt Id that woke the CPU up.

Example:

.. code-block:: c

   uint32_t data[3];
   data[0] = timestamp_went_sleep;
   data[1] = timestamp woke_up.
   data[2] = interrupt_id.


Task Monitor
------------

The task monitor tracks the activities of the task schedule server
in the microkernel and it is able to report three different types of
events related with the scheduler activities:


Task Monitor Task State Change Event
++++++++++++++++++++++++++++++++++++

The Task Monitor Task State Change Event tracks the task's status changes.
The event data is arranged as three 32 bit blocks:

* The first block contains the timestamp when the task server
  changed the task status.
* The second block contains the task ID of the affected task.
* The thid block contains a 32 bit number with the new status.

Example:

.. code-block:: c

   uint32_t data[3];

   data[0] = timestamp;
   data[1] = task_id.
   data[2] = status_data.

Task Monitor Kevent Event
+++++++++++++++++++++++++

The Task Monitor Kevent Event tracks the commands requested to the
task server by the kernel. The event data is arranged as two blocks
of 32 bits each:

* The first block contains the timestamp when the task server
  attended the kernel command.
* The second block contains the code of the command.

.. code-block:: c

   uint32_t data[3];

   data[0] = timestamp;
   data[1] = event_code.

Task Monitor Command Packet Event
+++++++++++++++++++++++++++++++++

The Task Monitor Command Packet Event track the command packets sent
to the task server. The event data is arranged as three blocks of
32 bits each:

* The first block contains the timestamp when the task server
  attended the kernel command.
* The second block contains the task identifier of the task
  affected by the packet.
* The thid block contains the memory vector of the routine
  executed by the task server.

Example:

.. code-block:: c

   uint32_t data[3];

   data[0] = timestamp;
   data[1] = task_id.
   data[2] = comm_handler.

Example: Retrieving Profiling Messages
======================================

.. code-block:: c

   uint32_t data[3];
   uint8_t data_length = SIZE32_OF(data);
   uint8_t dropped_count;

   while(1) {
      /* collect the data */
      res = sys_k_event_logger_get_wait(&event_id, &dropped_count, data,
         &data_length);

      if (dropped_count > 0) {
         /* process the message dropped count */
      }

      if (res > 0) {
         /* process the data */
         switch (event_id) {
         case KERNEL_EVENT_CONTEXT_SWITCH_EVENT_ID:
            /* ... Process the context switch event data ... */
            break;
         case KERNEL_EVENT_INTERRUPT_EVENT_ID:
            /* ... Process the interrupt event data ... */
            break;
         case KERNEL_EVENT_SLEEP_EVENT_ID:
            /* ... Process the data for a sleep event ... */
            break;
         case KERNEL_EVENT_LOGGER_TASK_MON_TASK_STATE_CHANGE_EVENT_ID:
            /* ... Process the data for a task monitor event ... */
            break;
         case KERNEL_EVENT_LOGGER_TASK_MON_KEVENT_EVENT_ID:
            /* ... Process the data for a task monitor command event ... */
            break;
         case KERNEL_EVENT_LOGGER_TASK_MON_CMD_PACKET_EVENT_ID:
            /* ... Process the data for a task monitor packet event ... */
            break;
         default:
            printf("unrecognized event id %d\n", event_id);
         }
      } else {
         if (res == -EMSGSIZE) {
            /* ERROR - The buffer provided to collect the
             * profiling events is too small.
             */
         } else if (ret == -EAGAIN) {
            /* There is no message available in the buffer */
         }
      }
   }

.. note::

   To see an example that shows how to collect the kernel event data, check the
   project :file:`samples/kernel_event_logger`.

Example: Adding a Kernel Event Logging Point
============================================

.. code-block:: c

   uint32_t data[2];

   if (sys_k_must_log_event(KERNEL_EVENT_LOGGER_CUSTOM_ID)) {
      data[0] = custom_data_1;
      data[1] = custom_data_2;

      sys_k_event_logger_put(KERNEL_EVENT_LOGGER_CUSTOM_ID, data, ARRAY_SIZE(data));
   }

Use the following function to register only the time of an event.

.. code-block:: c

   if (sys_k_must_log_event(KERNEL_EVENT_LOGGER_CUSTOM_ID)) {
      sys_k_event_logger_put_timed(KERNEL_EVENT_LOGGER_CUSTOM_ID);
   }

APIs
****

The following APIs are provided by the :file:`k_event_logger.h` file:

:cpp:func:`sys_k_event_logger_register_as_collector()`
   Register the current fiber as the collector fiber.

:c:func:`sys_k_event_logger_put()`
   Enqueue a kernel event logger message with custom data.

:cpp:func:`sys_k_event_logger_put_timed()`
   Enqueue a kernel event logger message with the current time.

:c:func:`sys_k_event_logger_get()`
   De-queue a kernel event logger message.

:c:func:`sys_k_event_logger_get_wait()`
   De-queue a kernel event logger message. Wait if the buffer is empty.

:c:func:`sys_k_event_logger_get_wait_timeout()`
   De-queue a kernel event logger message. Wait if the buffer is empty until the timeout expires.

:cpp:func:`sys_k_must_log_event()`
   Check if an event type has to be logged or not

In case KERNEL_EVENT_LOGGER_DYNAMIC is enabled:

:cpp:func:`sys_k_event_logger_set_mask()`
   Set kernel event logger event mask

:cpp:func:`sys_k_event_logger_get_mask()`
   Get kernel event logger event mask

:cpp:func:`sys_k_event_logger_set_monitor_mask()`
   Set task monitor event mask

:cpp:func:`sys_k_event_logger_get_monitor_mask()`
   Get task monitor event mask

In case KERNEL_EVENT_LOGGER_CUSTOM_TIMESTAMP is enabled:

:cpp:func:`sys_k_event_logger_set_timer()`
   Set kernel event logger timestamp function
