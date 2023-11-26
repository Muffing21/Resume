class Creator extends Phaser.Scene {
    constructor() {
        super("creatorScene");
    }

    preload() {
        //load the background image.
        this.load.image('kitchenBackground', './assets/kitchenTable.png');
    }

    create(){
        //show background
        this.add.tileSprite(0, 0, 1200, 700, 'kitchenBackground').setOrigin(0, 0);
        //UI and text

        let titleConfig = {
            fontFamily: 'Pangolin',
            fontSize: '32px',
            color: '#ffa90a',
            stroke: '#FFFFFF',
            strokeThickness: 2,
            align: 'right',
            fixedWidth: 0,
        }
        let text1Config = {
            fontFamily: 'Pangolin',
            fontSize: '24px',
            color: '#E66C2C',
            stroke: '#000000',
            strokeThickness: 2,
            align: 'right',
            fixedWidth: 0,
        }
        let creditConfig = {
            color: '#CD00CD',
            fontFamily: 'Pangolin',
            fontSize: '22px',
            stroke: '#FFFFFF', 
            strokeThickness: 3,
            align: 'left',
            fixedWidth: 0,
        }

        //menu text UI
        let centerX = game.config.width / 2;
        let centerY = game.config.height / 2;

        //add credits
        this.add.text(centerX, centerY-60, 'Our Group members:', titleConfig).setOrigin(0.5);
        this.add.text(centerX, centerY-20, 'Amanda Bahadori, Yunhan Wei, Wichapas Pichetpongsa, ZhiBin Huang', text1Config).setOrigin(0.5);

        this.add.text(centerX, centerY+10, 'Code Programmer:', titleConfig).setOrigin(0.5);
        this.add.text(centerX, centerY+50, 'Wichapas Pichetpongsa, Yunhan Wei, ZhiBin Huang', text1Config).setOrigin(0.5);

        // this.add.text(centerX, centerY-40, 'Sound Effect:', titleConfig).setOrigin(0.5);
        // this.add.text(centerX, centerY, 'Yunhan Wei', text1Config).setOrigin(0.5);

        this.add.text(centerX, centerY+90, 'Game Art:', titleConfig).setOrigin(0.5);
        this.add.text(centerX, centerY+130, 'Amanda Bahadori', text1Config).setOrigin(0.5);

        this.add.text(centerX, centerY+170, 'Music and SFX:', titleConfig).setOrigin(0.5);
        this.add.text(centerX, centerY+210, 'Yunhan Wei, ZhiBin Huang', text1Config).setOrigin(0.5);
        
        //type space to play
        this.add.text(centerX, centerY + 300, '[ Press (SPACE) to Return ]', creditConfig).setOrigin(0.5);
        //keyboard input
        keySPACE = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE);
    }

    update(){
        if(Phaser.Input.Keyboard.JustDown(keySPACE)){
            this.scene.start("menuScene");
        }
    }

    
}