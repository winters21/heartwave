# heartwave
Group Project of Team 21 for COMP 3004

Members: Shawn Sun, Jake Diedrich, Gabe Martell, Eve Nhan

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
