![petpreview](https://user-images.githubusercontent.com/80003435/144223734-b4140253-bc67-4501-8218-18dc4aa10471.png)

Virtual Companion Alpha v0.8.5
============================
A simple virtual pet, essentially a stat management game.
Track the project progress here: https://trello.com/b/dNvPpF1X/virtual-entity-alpha


Notes:
* issue - with Hunger and Thirst displaying Zero as a negtaive, caused by being a float. (with new gui not really an issue now as user cannot see this)
* issue - save and loading not working temporarily.

v0.8.5 changes:
-------------
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
Features currently implemented
---------------------------
- Feeding & Hunger
- Water & Thirst
- Initial Graphics


