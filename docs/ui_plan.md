=========================
OVERALL NOTES
=========================


- ftxui::Dimension controls screen size

- elements manage layout and are responsive to dimension changes

- will be able to handle the color dialogues fairly easily with the built in dropdown component, but since ftxui does not have a built in file dialog/browser, that may be tricky. 

- With FTXUI, it seems like the main hierarchy goes [Component -> Screen -> Loop]

1. Create component
2. Initialize a screen or screen interactive 
3. Start the main loop using screen.Loop(), passing in the top level component as an arg



With that in mind I'm planning to have one screen, with two documents. One document will be the main UI, then when the user starts a run the screen will switch to a different document containing elements that display the state of the emulator/rom such as register values.




=========================
MAIN DOCUMENT
=========================




