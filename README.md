# HeartWave
Group Project of Team 21 for COMP 3004 at Carleton University

Members: Shawn Sun, Jake Diedrich, Gabe Martell, Eve Nhan

## About the Project
This project involved the team designing and developing a functional device HeartWave.
A HeartWave is a device that measures, analyzes, and displays HRV (Heart Rate Variability) patterns through the use of an advanced heart rate monitor and provides users with real-time biofeedback based on their coherence levels.

This project is a visual representation of the device, and how it would operate in the real world on a real person. The program generates mock data that corresponds to the correct coherence levels of the person using the monitor.

Coherence is a state of synchronization between your heart, brain and autonomic nervous system that has been proven to have numerous mental, emotional and physical benefits.
There are many levels to this, but this project makes use of levels - Low, Medium, and High.

Depending on the level of coherence, it can generate a graph that can either be smooth or rough:
![image](https://github.com/winters21/heartwave/assets/77290127/498252d8-7e2d-4ab9-9077-5d30b6bb68a6)

The rougher graph shows a more LOWER coherence level, while the smoother graph shows a more HIGHER coherence level.
Coherence Scores can range from 0-16.

This was all taken into account when coming up with the algorithms for generating random data to be rendered. 

## How The Project Works
This project was written using `QT` in `C++`. This project is easy to setup using the `QTCreator IDE`. It gives you a visual window and is easy to use to setup clean User Interfaces using `QT C++`.

## User Interface
Settings:

![image](https://github.com/winters21/heartwave/assets/77290127/292d4609-8e81-4adf-ac24-5da17d62dcdc)

The settings allows you to set the proper settings needed for a session.

It allows you to set the breath pacer settings (Breath in and out) - 15s = 7.5 seconds breathing in, 7.5 seconds breathing out.

It allows you to set the proper coherence level (needed to generate the proper data)

As well as apply the device to your skin. This is also needed for the data generation.

HeartWave:

![image](https://github.com/winters21/heartwave/assets/77290127/1697b9c8-1853-4b45-b172-e3ec83a8b33f)

This is the actual device itself. As you can see, there is a lot going on.

The device shows the user when they are breathing in and out during a session based on the breath pacer setting. 

It also has lights above, indicating the coherence levels. These lights change color (i.e. light up!) when a user is in a particilar coherence level (Low, Medium, High)

We make use of `QCustomPlot` to render the graph. Each time we generate different heartbeats, we update the graph in real-time and display it on the monitor.

When starting a session, you will see the monitor will be on the screen with a "new session" text, just click the `OK` button to get started and the HeartWave will do its job!

The HeartWave does have a battery level and will run out of battery when it hits 0 (Top right corner), just click the charge battery button to fully charge the device.

Summary:

![image](https://github.com/winters21/heartwave/assets/77290127/c5f2c7cf-07ad-4299-8896-018e0a9b73e9)

This is the summary of the session that just happened. It shows the user all the important details of a session.

It displays the HRV graph, as well as highlights the session time, average coherence score, the achivement score, and the percentage spent in different coherence levels.

## What Each Member Worked On
### Jake Diedrich
- Worked on getting some of the basic UI elements set up and ready to use through MainWindow.
- Worked on implementing the QCustomPlot graph so that we can update the graph in real time with x and y elements.
- Worked on implementing some of the mediator class features to communicate with the MainWindow and HeartWave classes.
- Also worked on some documentation.
- Worked on the Log class to save current session logs as well as download a log file at the end of a session so the user can read the logs of their current session.
- Worked on getting the summary on the UI after a session ended, did everything in the summary except for the coherence percentages.
- Worked with Gabe on the UML diagram.

### Shawn Sun
- Worked on the menu in the MainWindow
- Started the Lights class to start with
- Worked on the mock class to generate heart rate based on three different coherence type: low, medium, and high
- Worked on getting the graph updated with the mock class in real time with time and heart rate as x and y elements respectively
- Bug fixed the mock class to have a more wave like line when plotting on the graph
- Bug fixed the session, particularly when in the summary, the results would show the time for a particular coherence was greater than session time, which gave a result of over 100%
- Reviewed and edited some documentation (use cases)
- Worked on some of the traceability matrix

### Gabe Martell
- Expanded UI design to a more modern-like display to the user in MainWindow.
- Worked on the coherence mock score generation in generateHeartRate() function.
- Worked on and implemented timers for updateAchievementScore(), updateHeartCoherence(), and updateSessionTime() in MainWindow. 
- That is, worked on the Achievement Score calculations, Coherence Score Light functionality, and Session Time counting respectively.
- Worked on summary of (Coherence Level / Session Time) percentage in createSummary() in MainWindow.
- Expanded on addToSystemLog() in the Log class to create new .txt files title (SessionNUM.txt) so that session text files are completed in numerical order.
- Worked on the OnSkin/OffSkin restriction and functionalities in MainWindow.
- Worked on Coherence class.
- Expanded on Sequence Diagrams so that it relates to, and is based off of, the more recent code changes.
- Worked with Jake on the UML Diagram.

### Eve
- Formatting and planning the contents idea for documentations.
- Designed the raw use cases ideas and detailed steps. 
- Designed the testing criterias for the program and wrote the traceability matrix.
- Designed the raw sequence diagram for the use cases.
- Worked on the use case diagram.
- Documentation reviews.


Organization of the submission: Use Cases, Sequence Diagrams, Traceability Matrix, Design Choices, Code

Requirements:
 - Dedicated memory size of at least 5000 MB
