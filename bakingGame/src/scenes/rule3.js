class Rule3 extends Phaser.Scene {
    constructor() {
        super("rule3Scene");
    }


    preload() {
        // load music audio
        // this.load.image('menucreator', './assets/intro1.png');
        //image
        this.load.image('cook', './assets/Oven_Sprite_Sheet.png');

        //load the background image.
        this.load.image('kitchenBackground', './assets/kitchenTable.png');
        
    }

    create (){
        //place background
        this.add.tileSprite(0, 0, 1200, 700, 'kitchenBackground').setOrigin(0, 0);

        let titleConfig = {
            fontFamily: 'Pangolin',
            fontSize: '28px',
            color: '#ffa90a',
            align: 'right',
            stroke: '#ff1493',
            strokeThickness: 6, 
            fixedWidth: 0,
        }

        let text1Config = {
            fontFamily: 'Pangolin',
            fontSize: '20px',
            color: '#461B7E',
            align: 'right',
            stroke: '#ff1493',
            strokeThickness: 6, 
            fixedWidth: 0,
        }
        
        let creditConfig = {
            color: '#CD00CD',
            fontFamily: 'Pangolin',
            fontSize: '20px',
            stroke: '#FFFFFF', 
            strokeThickness: 3,
            align: 'left',
            fixedWidth: 0,
        } 

        //menu text UI
        let centerX = game.config.width / 2;
        let centerY = game.config.height / 2;

        //First Step
        this.add.text(centerX, centerY -120, 'Second Step: Make the cake', titleConfig).setOrigin(0.5);
        this.add.text(centerX, centerY -30, 'Make sure to stir the bowl. Then, You will control the temperature to bake a perfect cake.', text1Config).setOrigin(0.5);
        this.add.text(centerX, centerY, 'There will be a temperature bar for you to control. Get the timing right!', text1Config).setOrigin(0.5);

        this.add.image(centerX, centerY +150, 'cook').setOrigin(0.5);

        //type space for next rule
        this.add.text(centerX, centerY + 300, '[ Press (SPACE) for next page ]', creditConfig).setOrigin(0.5);
        //keyboard input
        keySPACE = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE);

    }

    update (){
        if (Phaser.Input.Keyboard.JustDown(keySPACE)){
            this.scene.start('rule4Scene');
        }
    }
}