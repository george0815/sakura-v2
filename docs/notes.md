
1. Implement cartridge, test parsing rom data.
2. Wire up to basic UI (Only start and stop buttons for now).
3. Build out CPU core, wire it up to UI.


Right now this is the short term plan.


==================
> NOTES 
==================


--------
UI 
--------
- Need to do research on i18n, don't want to have to replace strings after building the UI [DONE: Using i18ncpp]
- Need to decide how to structure the UI, what components to use 
- Need to decide what to do about the debugging information that I plan to include (Have a section in the TUI or render it in the SDL window?) [DONE:  Will have a separate debugging screen then switch to it on rom load, then switch back to the normal UI when the rom is stopped]

CURRENT UI PLAN 
-------------------- 
1. Decide on i18n, how to switch strings based on the culture/lang setting [DONE: Using i18ncpp]
2. Once, decided, start implementing the resource string (assuming whatever solution I implement uses resource strings) [DONE]
3. Once i18n is setup, plan out the UI, boot up sakura v1 and plan the layout, decide the debugging question above 
4. Once everything is decided, start implementing the basic layout 


Things to keep in mind when deciding on what ftxui components to use 
- most submenus have to have vertical scroll
- dialog boxes for color settings were implemented kind of hacky in sakura v1, how will I implement it here 
- how will the ascii art look  
- someday in the future when I make snesquik v2 I would like to reuse this UI, so I will have to keep it loosely coupled with the NES core  



