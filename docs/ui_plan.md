

*******************************************************
MAIN 
*******************************************************

=========================
MAIN SCREEN
=========================

    - Container::Horizontal
        - TopRowComponenet 
        - BottomRowComponent


=========================
TOP ROW
=========================

 
    - Container::Horizontal
        - ASCII box (canvas)
        - Info box (Container::Horizontal or Container::Vertical depending on the settings)
        - Controls box (Container::Vertical)


=========================
BOTTOM ROW
=========================


    - Container::Horizontal
        - TabMenuComponent
            - Menu 
            - Button 

        - Container::Vertical 
            - Text 
            - TabContainerComponent (Container::Tab)


=========================
ROMS
=========================

    - TableComponent (from GeneralViews)


=========================
SAVES
=========================

    - Container::Horizontal
        - Menu
        - Container::Tab
            - TableComponent (from GeneralViews)
            - TableComponent (from GeneralViews)



=========================
SETTINGS
=========================

    - Container::Vertical 
        - Checkboxes  
        - Padding components (from GeneralViews)
        - TextInputComponents (from GeneralViews)
        - ColorComponents (from GeneralViews)
        - LanguageComponent (hbox with text + input)
        - Save Button 
        

=========================
CONTROLS
=========================

    - Container::Vertical
        - ControlOptionComponents (from GeneralViews)
        - Padding components (from GeneralViews)
        - Save button


=========================
LOG
=========================

    - Container::Vertical 
        - FocusableTextComponent (from GeneralViews) for each list/log item







*******************************************************
DEBUGGING SCREEN - TODO
*******************************************************



=========================
MAIN LAYOUT
=========================


- Window 
    - Container::Vertical 
        - Container::Horizontal
            - cpu state subcomponent
            - ppu state subcomponent
        - instructions subcomponents

=========================
PPU STATE
=========================


- Window 
    - Container::Vertical 
        - Text 
        - Text 
        - Text 
        - Text 
        - Text 
        - Text 
        - Text 



=========================
CPU STATE
=========================


- Window 
    - Container::Vertical 
        - Text 
        - Text 
        - Text 
        - Text 
        - Text 
        - Text 
        - Text 


=========================
INSTRUCTIONS
=========================

- Window 
    - Container::Vertical




