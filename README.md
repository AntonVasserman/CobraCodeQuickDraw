# Quick Draw (with C++)
This is a Repository for Quick Draw, a Game Project from Cobra Code's Udemy course.

As a challenge to practice and improve my C++ and Coding in Unreal Engine, this project is done using C++ rather than Blueprints.

## References

Cobra Code on Udemy: https://www.udemy.com/user/stephen-knall-2/ <br>
The Udemy Course: https://www.udemy.com/course/unreal-2d-course/

## Additional Features (not included in the course)

### Refactoring:

TODO:

1. Inputs are being handled via a PlayerController
2. AI is being handled via an AIController
3. Phase state moved into a GameState class

WIP:

1. Camera and Player Character are being initiated via PlayerStart as should

Done:

1. Game-loop is handled via Phase Change Event instead of GameMode handling everything
2. Exclamation Mark moved to be a Widget instead of a Sprite Actor 

### New Features:

TODO:
1. Attack is done via a Combination of Buttons in an Order
2. Added support for multiple enemies, specifically added minions to accompany the Toad Samurai (this results in a Ghost of Tsushima like duel)
3. Draw indicator improved by adding sound and draw animations
4. Added Score per enemy defeated
5. Added multiple levels with difficulty set by a Data Table with the Game Loop playing until player loses
6. Added Main Menu
7. Added persistence for score and high score
8. Added Sound & FX

Done: