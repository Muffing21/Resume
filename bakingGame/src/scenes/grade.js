class grade extends Phaser.Scene {
    constructor() {
        super('gradeScene');
    }

    preload(){
        this.load.path = 'assets/';

        this.load.image('invisWall', 'invisWall2.png');
        this.load.image('gamebar', 'gamebar.png');
        this.load.image('gamebar2', 'gamebar2.png');
    }

    create(data){
        this.time = data;
        this.defaultTime = 60000;
        this.score = 1;
        keyZ = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.Z);
        this.add.image(config.width/2, config.height/2, 'chef');
        //this.currentTime = (this.time/1000).toFixed(2);
        this.currentTime = this.add.text(config.width/2, config.height/2+200, (this.time/1000).toFixed(2), scoreConfig);
        this.add.text(config.width/2-150, config.height/2+200, 'Your Time:', scoreConfig);
        this.add.text(config.width/2-150, config.height/2+250, 'Press z to go back to menu', scoreConfig);


    }


    update(){
        if(this.time <= this.defaultTime){
            this.add.text(config.width/2, config.height/2, 'S   RANK: Baking Master', scoreConfig).setOrigin(0.5);
        }
        if(this.time > this.defaultTime && this.time <= this.defaultTime+5000){
            this.add.text(config.width/2, config.height/2, 'A   RANK: Baking Professional', scoreConfig).setOrigin(0.5);
        }
        if(this.time > this.defaultTime+5000 && this.time <=this.defaultTime+10000){
            this.add.text(config.width/2, config.height/2, 'A-   RANK: Baking Elite', scoreConfig).setOrigin(0.5);
        }
        if(this.time > this.defaultTime+10000 && this.time <= this.defaultTime+15000){
            this.add.text(config.width/2, config.height/2, 'B   RANK: Average Baker', scoreConfig).setOrigin(0.5);
        }
        if(this.time > this.defaultTime+15000 && this.time <= this.defaultTime+20000){
            this.add.text(config.width/2, config.height/2, 'B-   RANK: Below Average Baker', scoreConfig).setOrigin(0.5);
        }
        if(this.time > this.defaultTime+20000 && this.time <= this.defaultTime+25000){
            this.add.text(config.width/2, config.height/2, 'C    RANK: Baking Beginner', scoreConfig).setOrigin(0.5);
        }
        if(this.time > this.defaultTime+25000 && this.time <= this.defaultTime+30000){
            this.add.text(config.width/2, config.height/2, 'C-   RANK: Baking Newbie', scoreConfig).setOrigin(0.5);
        }
        if(this.time > this.defaultTime+30000 && this.time <= this.defaultTime+35000){
            this.add.text(config.width/2, config.height/2, 'D   RANK: What Are You Doing?', scoreConfig).setOrigin(0.5);
        }
        if(this.time > this.defaultTime+35000 && this.time <= this.defaultTime+40000){
            this.add.text(config.width/2, config.height/2, 'D-   RANK: How?!', scoreConfig).setOrigin(0.5);
        }
        if(this.time > this.defaultTime+40000){
            this.add.text(config.width/2, config.height/2, 'F   RANK: You Donkey!', scoreConfig).setOrigin(0.5);
        }

        if(Phaser.Input.Keyboard.JustDown(keyZ)){
            
            this.scene.start('menuScene');
        }

    }

}