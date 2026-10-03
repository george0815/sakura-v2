=========================
OVERALL NOTES
=========================


- ftxui::Dimension controls screen size

- Elements manage layout and are responsive to dimension changes

- Will be able to handle the color dialogues fairly easily with the built in dropdown component, but since ftxui does not have a built in file dialog/browser, that may be tricky. 

- With FTXUI, it seems like the main hierarchy goes [Component -> Screen -> Loop]

- In this plan, when I say "subcomponent" I basically mean a custom component comprised of other components

- Remember to use Renderer to decorate 

1. Create component
2. Initialize a screen or screen interactive 
3. Start the main loop using screen.Loop(), passing in the top level component as an arg



With that in mind I'm planning to have one screen, with two documents. One document will be the main UI, then when the user starts a run the screen will switch to a different document containing elements that display the state of the emulator/rom such as register values.



=========================
MAIN DOCUMENT
=========================

- Main container:  Container::Vertical (or vbox) with border 
    - Top row: Container::Horizontal (or hbox) without border 
        - ASCII Box : Canvas with border 
        - Info: Container::Vertical (or vbox) without border  
            - Text
            - Text
        - controls: Container::Vertical (or vbox) without border
            - ControlList component (A list of strings that has the controls) 

    - Bottom row: Renderer/hbox
        - Tab menu: vbox with border
            - menu component
            - exit button
        - Tab container: Container::Tab 
            - window (menu named passed as arg)




=========================
ROMS
=========================

    - Table 



=========================
SAVES
=========================

    - Tab menu: Container::Vertical with border 
    - Tab container: Container::Tab 
        - Save menu subcomponent 
            - Window 
                - Table 


=========================
SETTINGS
=========================

    - Container::Vertical 
        - Checkbox 
        - Checkbox 
        - Checkbox 
        - Checkbox 
        - TextInput subcomponent (hbox with text + input)
        - TextInput subcomponent (hbox with text + input)
        - TextInput subcomponent (hbox with text + input)
        - TextInput subcomponent (hbox with text + input)
        - TextInput subcomponent (hbox with text + input)
        - ColorInput subcomponent (hbox with text + dropdown)
        - ColorInput subcomponent (hbox with text + dropdown)
        - ColorInput subcomponent (hbox with text + dropdown)
        - ColorInput subcomponent (hbox with text + dropdown)
        - ColorInput subcomponent (hbox with text + dropdown)
        - ColorInput subcomponent (hbox with text + dropdown)
        - Checkbox 
        - Button 
        

=========================
CONTROLS
=========================

    - Container::Vertical
        - Control setting subcomponents (text and button)
        - Save button


=========================
LOG
=========================

    - Container::Vertical 
        - Text 


