# Development

---
4/14
- Linked and added Fast CSV external library
- Able to build cinder app, but cant add the header to source files
- Either figure out how to make this library work or find another one


4/18
- Pivoted on game idea based on data available for use in the program
- Found a spreadsheet with loads of stats for current and historic nba player seasons from FiveThirtyEight.com
- Unable to find similar free resources for college player stats
- Switched from comparing college to nba players to comparing nba season to other nba seasons

4/20
- Started updated the gui of the app using base cinder app functions
- Added InteractiveObjects and text boxes to try and create interface
- Faced issues with flickering text fields and unable to properly add functionality when
 clicked or text entered
- Want to find a simple and useful external library or cinder block for GUI

4/24
- Found and added Cinder-ImGui block from github and cloned the repo to the blocks folder in cinder app
- Used ImGui to add simple instructions and player search bar for user to enter desired player
- PLan to use its menu features to display the similar nba player seasons

4/30
- Found problems using the lite csv parser as I was unable to target specific columns to extract desired info
- Tried other two csv readering external libraries from the list
- Had problems with the library files themselves as they had type conversion errors and was unable to build app
- Need to figure out a new way to read info from large csv file

5/5
- Tried implementing cinder blocks for reading csv files
- Had problems implementing and using OpenCV and OpenCV3 

5/6
- Able to read and load csv file and find player season and stats based on user input
- Used all stats to find season find the most categories within 5% to determine "similarity percentage"
