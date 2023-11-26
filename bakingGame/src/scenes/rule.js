class Rule extends Phaser.Scene {
    constructor() {
        super("ruleScene");
    }


    preload() {
        //image
        this.load.image('character','./assets/idle.png');
        //image
        this.load.image('kitchen','./assets/kitchen.png');
        this.load.image('kitchenBackground', './assets/kitchenTable.png');
    }

    create (){
        //show background
        this.add.tileSprite(0, 0, 1200, 700, 'kitchen').setOrigin(0, 0);

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
            color: '#ff69b4',
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

        //'Character will keep running until you are caught by the skeleton!'
        this.add.text(centerX, centerY -300, 'Some people like cake but lack the skill to bake....', titleConfig).setOrigin(0.5);
        this.add.text(centerX, centerY -250, 'Do you want to be the "Master of Baking?"', titleConfig).setOrigin(0.5);
        this.add.text(centerX, centerY -200, ' What are you waiting for? Come over and Try!', titleConfig).setOrigin(0.5);

        this.add.image(centerX - 25, centerY - 40, 'character').setOrigin(0.5);

        this.add.text(centerX, centerY + 150, 'You will control a cute, lovely character. ', text1Config).setOrigin(0.5);
        this.add.text(centerX, centerY + 200, 'The baking score is based on how long it took you to make the cake.', text1Config).setOrigin(0.5);
        //text1Config.color = '#FFFFFF';
        // this.add.text(centerX, centerY + 100, 'Up Arrow Once: jump', text1Config).setOrigin(0.5);
        // this.add.text(centerX, centerY + 150, 'Up Arrow Twice: double jump', text1Config).setOrigin(0.5);
        // this.add.text(centerX, centerY + 200, 'Hold Right Arrow: always, to move right slightly when jumping', text1Config).setOrigin(0.5);
        
        //this.add.image(centerX - 160, 80, 'character').setScale(0.7).setOrigin(0.5);
        //type space to play
        this.add.text(centerX, centerY + 250, '[ Press (SPACE) for next page ]', creditConfig).setOrigin(0.5);
        
        //keyboard input
        keySPACE = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE);

    }

    update (){
        if (Phaser.Input.Keyboard.JustDown(keySPACE)){
            this.scene.start('rule1Scene');
        }
    }
}