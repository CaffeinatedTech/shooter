Contributing to this project
============================

The point of this project is for me (CaffeinatedTech) to 
learn and practice C++ and SFML by building a game.

You are welcome and encouraged to contribute by submitting 
enemy ships which will be used in the game.

### Restrictions
Please do not supply copyrighted material.  All sprites in this project must be royalty free.  
Sprite images must be PNG format with transparency background.

### Procedure
This is a rough procedure of how to go about contributing enemies to this project.
* Fork this repository (top right corner)  
![fork repo](https://raw.githubusercontent.com/CaffeinatedTech/docimages/main/github/fork_repo.png)

#### Enemy XML
* Locate the `assets/enemies` directory
* copy the contents of `enemy1.xml`
* create a new file called for example `charlie.xml`
* paste the contents from enemy1
* alter the properties of your enemy.  Specifically the
health, scores, sprite file, and abilities.
* If you don't contribute a sprite, then please use one of the
existing ones found in the `assets/enemies/sprites` directory.  use the filename of the chosen sprite in the xml `enemy1.png` for example.
* Commit New File selecting `create a new branch`  
![commit new branch](https://raw.githubusercontent.com/CaffeinatedTech/docimages/main/github/commit-new_branch.png)

#### Enemy Sprite
If you are supplying an enemy sprite (thank you) - then you need to make sure that you have referenced the sprite name in your XML.
* Make sure that you are in your new branch that you created when you commited your new XML
* Upload your sprite to `assets/enemies/sprites` directory
* Commit this file to your new branch
* Click `Pull Requests`
* Create a new Pull Request from your new branch in your repo to mine
* ...
* Profit

If you get stuck and have further questions, then please hit me up on discord [CaffeinatedTech](https://discord.gg/QTFPXK6) and I will help you out.
 
