// Jim Whitehead, based on Movement Studies by Nathan Altice
// Updated: 5/1/2022
// Phaser 3 Texture Atlas plus movement dust cloud particle system
// Concepts: Arcade physics, texture atlas animation, particle systems
// The example atlas is commercial and should not be used for your own projects 
// Source: https://www.pinterest.com/pin/700802392005070604/ (but this is likely ripped from a game)

// Interpret JavaScript strictly (see: https://www.w3schools.com/js/js_strict.asp)
// Helps with not using undeclared variables

//the menu image for now: Testing case
//link: https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.pinterest.com%2Fpin%2F15621929940367318%2F&psig=AOvVaw02ZjJd4wiOKrHKUY0moQ5P&ust=1652751406455000&source=images&cd=vfe&ved=0CAwQjRxqFwoTCJjfqfbw4vcCFQAAAAAdAAAAABAN
'use strict';

// global variables
let cursors;

// main game object
let config = {
    type: Phaser.WEBGL,
    width: 1024,
    height: 672,
    physics: {
        default: 'arcade',
        arcade: {
            debug: false,
            gravity: {
                x: 0,
                y: 0
            }
        }
    },
    scene: [Menu, Creator, Rule, Rule1, Rule2, Rule3, Rule4, Load, Title, restaurant, ingredients, stir, restaurant2, baking, decorating, grade, Talking]
};

let scoreConfig = {
    fontFamily: 'Pangolin',
    fontSize: '20px',
    color: '#F8B88B',
    align: 'right',
    stroke: '#FF6700',
    strokeThickness: 6, 
    fixedWidth: 0,
    padding: {
        top: 10,
        bottom: 10,
        }, 
    };
    //fixedWidth: 

//let time = 0;
this.gameOver = false;
this.playerGrade == 100;
this.music;

let game = new Phaser.Game(config);

// globals
const centerX = game.config.width / 2;
const centerY = game.config.height / 2;

// set UI sizes
let borderUISize = game.config.height / 15;
let borderPadding = borderUISize / 3;

let keyUp, keyDown, keyRight, keyLeft, keySPACE, keyZ, keyX, keyS, KeyW, keyA;
