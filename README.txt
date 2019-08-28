TEXT ADVENTURE

File made by makefile is "adventure"

This game takes place on UMass, with interactions based on the classes CS 230 and CS 240. The game is a linear, exploration based game with various rooms
to visit and items to use. The basic goal of the game is to maximize your player stat of "gope", which will go up or down based on choices that the player
makes in his game time. The game will end when the player enters the final room, and will trigger certain endings based on how much gope the player was
able to collect.

The way the game generates the rooms is using various random numbers (direction, item count, and item id's). These allow for the gameplay to be different
for each subsequent run. The number of rooms is dependent on ROOM_COUNT (currently set to 10). The game design is fairly linear where there is one winding
path to follow along.

There are 5 kinds of rooms and every room has 6 exits, though they may be locked, unlocked, or simply walled off. The unlocked exits can be gone through, 
but any locked exits must be unlocked using a Door Key (altering the state of the room). Every room has the potential to contain items. These items are 
dependent on the type of room and the number of items varies from 2 to 4 for each room (arbitrary range) and scattered around the room. Note that there can
be several of one type of item in a room. The items can be put int the player's backpack. The backpack has a default capacity to conatin DEFAULT_BACKPACK 
(set to 5) items. You can store more types of items by reading books you find. Alternatively, you can just drop a type of item. 

Commands (case sensitive):

look - Shows a description for the room, the connecting exits, items in the room, and contents of backpack.
go [DIRECTION] - Used to go through a valid (unlocked) exit. Ex. "go north"
take [ITEM NAME] - Used to take an item from the current room and store it in the backpack (given enough space). Ex. "take Programming In C (3rd Edition)"
drop [ITEM NAME] - Drops all counts of the item name. Ex. "drop Phone"
use [ITEM NAME] - Uses the item you specify to either alter either your state or the room state (or just displays a snarky message). Ex. "use General Tso's Peppers"

Video link:
https://docs.google.com/document/d/1H7hHS8Oq-DyJSQ-qj1RLzBRDOe3wiUaDGZRVtDPX5NM/edit?usp=sharing