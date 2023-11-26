class Title extends Phaser.Scene {
    constructor() {
        super("titleScene");
    }

    preload() {

        this.load.image('kitchen','./assets/kitchen.png');
        this.load.image('kitchenBackground', './assets/kitchenTable.png');

        // load assets
        this.load.path = "./assets/";

        // load JSON (dialog)
        this.load.json('dialog', 'json/dialog.json');

        // load images
        this.load.image('dialogbox', 'img/dialogbox.png');
        //image for you
        this.load.image('You', 'img/player.png');
        //image for jim
        this.load.image('Gorgon', 'img/chef.png');

        //load the background

        // load bitmap font
        this.load.bitmapFont('gem_font', 'font/gem.png', 'font/gem.xml');
    }

    create() {
        //load the image
        this.add.tileSprite(0, 0, 1200, 700, 'kitchen').setOrigin(0, 0);
        //this.add.tileSprite(0, 0, 1200, 700, 'kitchenBackground').setOrigin(0, 0);

        // add title text
        this.add.bitmapText(centerX, centerY - 32, 'gem_font', 'Welcome to Hells Bakery', 32).setOrigin(0.5);
        this.add.bitmapText(centerX, centerY, 'gem_font', 'Press SPACE to talk with Gorgon Baguette', 16).setOrigin(0.5);
        this.add.bitmapText(centerX, centerY + 32, 'gem_font', 'Press S to skip and get Start', 16).setOrigin(0.5);
        this.add.bitmapText(centerX, centerY + 64, 'gem_font', 'Press Z to go back to menu', 16).setOrigin(0.5);


        //key s
        keyS = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.S);
        keyZ = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.Z);

        // create input
        cursors = this.input.keyboard.createCursorKeys();
    }

    update() {
        // wait for player input
        if(Phaser.Input.Keyboard.JustDown(cursors.space)) {
            this.scene.start("talkingScene");
        }
        if(Phaser.Input.Keyboard.JustDown(keyS)) {
            this.scene.start("loadScene");
        }
        if(Phaser.Input.Keyboard.JustDown(keyZ)) {
            this.scene.start("menuScene");
        }
    }
}