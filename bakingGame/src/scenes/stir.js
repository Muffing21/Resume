class stir extends Phaser.Scene{
    constructor(){
        super("stirScene")
        //this.cursors=this.scene.input.keyboard.createCursorKeys()
        this.counter=0;
        this.up_pressed=false;
        this.down_pressed=false;
        this.left_pressed=false;
        this.right_pressed=false;
        
    }
    
    // preload(){
    //     this.load.path = 'assets/';
    //     this.load.image('background','LoZ-overworld-up.gif');
    //     this.load.image('character','temp.png');
    // }
    create(data){

        this.bg = this.add.image(0, 0, 'kitchenTable').setOrigin(0);
        keyUp = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.UP);
        keyLeft = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.LEFT);
        keyRight = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.RIGHT);
        keyDown = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.DOWN);
        this.music = this.sound.add('menu_bgm', {mute: false, volume: 1.0, rate: 1, loop: true});
        this.music.play();
        
        this.counter_text=this.add.text(config.width/2, config.height/2-200,this.counter,scoreConfig);
        this.add.text(config.width/2, config.height/2+200, 'press left, up, right,\nand down arrow to stir to 50',scoreConfig);

        //add bowl
        this.bowl = this.add.sprite(config.width/2, config.height/2, 'stir');
        //bg
        

        //create our animation
        this.anims.create({
            key: 'stir',
            frames: this.anims.generateFrameNumbers('stir', {frames: [1, 2, 3, 4, 5]}),
            framerate: 12,
            repeat: 0
        });
        
        this.time = data
        //timer
        this.currentTime = this.add.text(20, 20, this.time, scoreConfig);

        //keyboard
        keySPACE = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE);

    }
    update(time, delta){
        
        this.time += delta;
        this.currentTime.text = (this.time/1000).toFixed(2);
        
        if(Phaser.Input.Keyboard.JustDown(keyUp)&&this.right_pressed==false&&this.left_pressed==false&&this.up_pressed==false&&this.down_pressed==false){
            this.counter++;
            this.counter_text.text=this.counter;
            this.up_pressed=true;
            this.bowl.anims.play('stir');

        }
        if(Phaser.Input.Keyboard.JustDown(keyRight)&&this.right_pressed==false&&this.left_pressed==false&&this.up_pressed==true&&this.down_pressed==false){
            this.counter++;
            this.counter_text.text=this.counter;
            this.right_pressed=true;


        }
        if(Phaser.Input.Keyboard.JustDown(keyDown)&&this.right_pressed==true&&this.left_pressed==false&&this.up_pressed==true&&this.down_pressed==false){
            this.counter++;
            this.counter_text.text=this.counter;
            this.down_pressed=true;

        }
        if(Phaser.Input.Keyboard.JustDown(keyLeft)&&this.right_pressed==true&&this.left_pressed==false&&this.up_pressed==true&&this.down_pressed==true){
            this.counter++;
            this.counter_text.text=this.counter;
            this.up_pressed=false;
            this.right_pressed=false;
            this.down_pressed=false;
            this.bowl.anims.play('stir');
            
        }        
        
        if(this.counter >= 50){
            this.music.stop();
            this.scene.start('restaurant2Scene', this.time);
        }
    }
}