Virtual Companion Alpha v0.7
============================
A simple virtual pet, essentially a stat management game.
Uses ImGui for the interface.

Notes: Currently most features working as intended.
Next update will change the way the pet eats and drinks - instead of consuming food and water in fractions, larger chunks will be consumed to reflect bites.
- will remove multiple pets also, so the user has less to manage.

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
* ImGui 1.83
* SFML 2.5.1
* ImGui-SFML v2.3
* Sqlite 3

---------------------------
Features in this version
---------------------------
- Feeding & Hunger
- Multiple Food Types
- Water & Thirst
- Visual Representaion


