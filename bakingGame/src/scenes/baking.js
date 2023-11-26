class baking extends Phaser.Scene{
    constructor(){
        super("bakingScene")

    }
    preload(){
        this.load.path = 'assets/';
        this.load.image('mb','movingblock.png');
        this.load.image('a','invisible_block.png');
        this.load.image('rd', 'red_block.png');
        this.load.image('bar','bar.png');
        this.load.audio('sfx', 'sfx.wav');

        this.load.image('safeZone', 'safeZone.png');
        this.load.image('dangerBar', 'dangerBar.png');
        this.load.image('movingBlock', 'movingblock.png');

        //baking scene
        this.load.spritesheet('bake', 'bake.png', {frameWidth: 256, frameHeight: 256, startFrame: 0, endFrame: 3});

    }
    

    create(data){
        //this.add.image(600,40,'background');
        var position_value = Phaser.Math.Between(0, 1024);
        this.moving_speed=840;
        this.a = false;
        this.count=0;
        keySPACE = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE);
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
            //fixedWidth: 
        }

        this.sfx = this.sound.add('sfx', {mute: false, volume: 1.0, rate: 1, loop: false});

        this.music = this.sound.add('menu_bgm', {mute: false, volume: 1.0, rate: 1, loop: true});
        this.music.play();

        this.bg = this.add.image(0, 0, 'kitchenTable').setOrigin(0);
        this.baking = this.add.sprite(config.width/2, config.height/2, 'bake');

        this.anims.create({
            key: 'bake',
            frames: this.anims.generateFrameNumbers('bake', {frames: [0, 1, 2, 3]}),
            frameRate: 8,
            repeat: 0
        });


        
        this.block = this.add.image(512,40,'dangerBar');
        this.rd=this.physics.add.image(position_value,40,'safeZone');
        this.mb=this.physics.add.image(300,30,'movingBlock');

        this.scoreText=this.add.text(20,90,'SCORE:0', scoreConfig);
        this.physics.add.collider(this.mb,this.i_1);
        this.physics.add.collider(this.mb,this.i_2);   
        this.mb.setVelocity(this.moving_speed,0);
        this.mb.setBounce(1,1);
        this.mb.setCollideWorldBounds(true);
        this.physics.add.overlap(this.mb, this.rd);
        //this.mb.setBounce(1,1);

        this.time = data
        //timer
        this.currentTime = this.add.text(200, 200, this.time, scoreConfig);

    }

    update(time, delta){

        this.time += delta;
        this.currentTime.text = (this.time/1000).toFixed(2);

        this.a = this.mb.body.touching.none ? false :true;
        if(Phaser.Input.Keyboard.JustDown(keySPACE) && this.a){
            this.baking.anims.play('bake');
            this.sfx.play();
            //this.scene.start('testScene');//change this <-
            this.mb.setPosition(330,40);
            this.rd.setPosition(Phaser.Math.Between(0, 600),40);
            this.count++;
            this.scoreText.setText('SCORE:'+this.count);
            this.moving_speed=this.moving_speed+100;
            this.mb.setVelocity(this.moving_speed,0);
            console.log(this.moving_speed);
        }

        if(this.count == 5){
            this.music.stop();
            this.scene.start('decoratingScene', this.time);    
        }
    }

}
