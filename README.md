
![gitsplash_wide](https://i.imgur.com/UJdZQJi.png)

Virtual Companion Alpha v0.9
============================
A simple virtual pet, essentially a stat management game.
Track the project progress here: https://trello.com/b/dNvPpF1X/virtual-entity-alpha

v0.9 changes:
--------------
* added updated placeholder sprites for food and feed button
* added age counter in top left corner
* added pet animations back

Notes:
- few bugs regarding hunger & digesting, probably a logic problem - looking at simplifying digestion process

v0.8.7 changes:
--------------
* removed shop feature for now
* added gui exit button
* added heart visuals to track health

v0.8.6 changes:
--------------
* removed multiple pets
* cleaned and refactored a lot to suit the new gui 

Notes:
* issue - new gui elements working but with a few bugs

v0.8.5 changes:
---------------
* added initial alpha gui and graphics
* removed ImGui
* removed ImGui-SFML v2.3
* removed Sqlite 3

v0.8 changes:
-------------
* eating and drinking rates have been changed to more realistic variables (so it's more familiar for user)
* the higher the hunger and thirst level, the faster they are consumed
* fixed Jor El, Zoidberg and Mr Biggles Worth eating Zoidbergs food
* added deeper stats progress bars for stomach, digestion, consumed water, and bladder
* changed progress bar colours
* some refactoring & restructuring

v0.7 changes:
-------------
* added all planned food items, with their individual variables
* changed living variables to reflect the original plans
* added a few checks to clamp values
* database.cpp removed from build until updated to reflect changes

v0.65 changes:
-------------
* fixed food and feeding not working
* images of pet now load and change depending on conditions

v0.6 changes:
-------------
* merged some files to make things easier
* tweaked the layout

v0.5 changes:
-------------
* first attempt at adding visual representation of companion
* Issue: image not loading, think its something to do with opengl 

v0.4 changes:
-------------
* Initial Upload

------------
Dependencies
------------
* SFML 2.5.1

---------------------------
Current Features
---------------------------
- Feeding & Hunger
- Water & Thirst
- Placeholder Graphics
- Ageing


