class Rule1 extends Phaser.Scene {
    constructor() {
        super("rule1Scene");
    }


    preload() {
        // load music audio
        // this.load.image('menucreator', './assets/intro1.png');
        //image
        this.load.image('walk_up','./assets/walkup.png');
        this.load.image('walk_down','./assets/walkdown.png');
        this.load.image('walk_left','./assets/walkleft.png');
        this.load.image('walk_right','./assets/walkright.png');

        this.load.image('Background', './assets/menu_bg.png');
    }

    create (){
        //place background
        this.add.tileSprite(0, 0, 1200, 700, 'Background').setOrigin(0, 0);

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
            color: '#36013F',
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

        //'Character will keep running until you are caught by the skeleton!'
        this.add.text(centerX, centerY -300, 'Base movement for Jim WhiteHead.', titleConfig).setOrigin(0.5);
        //image move up
        this.add.image(centerX, centerY - 230, 'walk_up').setOrigin(0.5);
        this.add.text(centerX, centerY -160, 'Hold Up Arrow: Allow Jim can move up', text1Config).setOrigin(0.5);
        //image move right
        this.add.image(centerX, centerY - 95, 'walk_right').setOrigin(0.5);
        this.add.text(centerX, centerY -25, 'Hold Right Arrow: Allow Jim move right', text1Config).setOrigin(0.5);
        //image move left
        this.add.image(centerX, centerY +40, 'walk_left').setOrigin(0.5);
        this.add.text(centerX, centerY +110, 'Hold Left Arrow: Allow Jim move left', text1Config).setOrigin(0.5);
        //image move down
        this.add.image(centerX, centerY +180, 'walk_down').setOrigin(0.5);
        this.add.text(centerX, centerY +260, 'Hold Down Arrow: Allow Jim move down', text1Config).setOrigin(0.5);

        //type space for next rule
         this.add.text(centerX, centerY + 300, '[ Press (SPACE) for next page ]', creditConfig).setOrigin(0.5);
        //keyboard input
        keySPACE = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE);

    }

    update (){
        if (Phaser.Input.Keyboard.JustDown(keySPACE)){
            this.scene.start('rule2Scene');
        }
    }
}