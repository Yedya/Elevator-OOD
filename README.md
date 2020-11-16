# OOP - Elevator System

Prompt: "Design an elevator system for a building."

OOP questions are often meant to be broad and open ended. They are usually designed to test your ability to work with vague constraints, and see how you go about making a problem more specific and offering up a solution that takes into account various tradeoffs.

The idea is that they want to see how you'll perform in a real world work scenario where you have to build something with vague requirements and how you'll make key decisions that might have a lasting impact on the project.

# Objects

These are the objects/classes you should build out:

* `Elevator` class
* `Building` class
* `Person` class

Potential Helper Classes:
* `Floor` class
* `Button` class

# Good Clarifying Questions to Ask

**1) What is the goal? What should I optimize for?**

You should balance **minimizing** wait times for individuals and picking people up in a **first-come-first serve** order.

**2) What are the building/floor specs?**

General purpose building, 40 floors.

100 people per floor.

**3) What are the specs of the elevator?**

Each elevator can hold 1500 lbs at once.

Each elevator should have buttons for each floor.

To add more complexity, think about adding the emergency button, or restricting floor access.

**3) What are the specs of the person class?**

Pretty straightforward and can have a number of properties.

But the important one is having a weight property.


**4) What are some user stories?**

People should be able to request elevators going in a certain direction.

Elevators should be able to drop people off on different floors.

There should be a way of directing requests to different elevators based on proximity and direction.


# Other Questions to Consider

1) Where do you place an elevator that isn’t occupied?

2) How does the system know which elevator to send to a request?

3) How does adding more elevators change the algorithm to determine elevator route?

4) What is the composition of each object i.e., what exists within what?

5) Are the objects ensuring good encapsulation of data? Am I restricting unnecessary access to data?


# General Approach

Don't start by trying to figure out what classes should exist where and what they should do.

Think about the whole system, and the **event** that take place.

Think of the **life-cycle** of handling a single elevator request.

Start simple: one person, one floor, one elevator.

Then add more floors, more people, people going in different directions, and finally more elevators.

Often OOP problems are hiding implicit algorithm problems within themselves (here it's how to manage the order of requests within an elevator).

But the difficulty usually doesn't lie in the use of a complex algorithm. It has more to do with there being a LOT of simple moving parts to account for. That's where the complexity comes from.

# Example of Potential Design

![Elevator System](https://res.cloudinary.com/outco-io/image/upload/v1536777915/Elevator_System.png)


#### Zoom Link:
[2019.10.08 - Design Elevator System](https://zoom.us/recording/share/7PmhoI43J_-emRwsMZme5Sgihbx3CSF7WDLRZ2PZ8oawIumekTziMw)

#### Slides:
[2019.10.08 - OOD Example Flow](https://res.cloudinary.com/outco-io/image/upload/v1572302784/OOD_Example_Flow.pdf)
