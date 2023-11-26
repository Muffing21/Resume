class Rule2 extends Phaser.Scene {
    constructor() {
        super("rule2Scene");
    }


    preload() {
        // load music audio
        // this.load.image('menucreator', './assets/intro1.png');
        //image
        this.load.image('first_step', './assets/Bowl_Sprite_Sheet.png');
        this.load.image('second_step', './assets/butter.png');
        this.load.image('third_step', './assets/milk.png');

        //load the background image.
        //this.load.image('kitchenBackground', './assets/kitchentable.png');
        
    }

    create (){
        //place background
        //this.add.tileSprite(0, 0, 1200, 700, 'kitchenBackground').setOrigin(0, 0);

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
            color: '#ff1493',
            align: 'right',
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
        this.add.text(centerX, centerY -300, 'First Step: Gather the ingredients', titleConfig).setOrigin(0.5);
        this.add.text(centerX, centerY -260, 'Check the recipe on what to gather. The, start putting them in the bowl.', text1Config).setOrigin(0.5);

        this.add.image(centerX, centerY -100, 'third_step').setOrigin(0.5);
        this.add.image(centerX, centerY +20, 'second_step').setOrigin(0.5);
        this.add.image(centerX, centerY +200, 'first_step').setOrigin(0.5);

        //type space for next rule
        this.add.text(centerX, centerY + 300, '[ Press (SPACE) for next page ]', creditConfig).setOrigin(0.5);
        //keyboard input
        keySPACE = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE);

    }

    update (){
        if (Phaser.Input.Keyboard.JustDown(keySPACE)){
            this.scene.start('rule3Scene');
        }
    }
}