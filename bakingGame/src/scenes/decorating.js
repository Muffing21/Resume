class decorating extends Phaser.Scene{
    constructor(){
        super("decoratingScene");    
    }
    
    
    create(data){
        this.count=0;
        this.score=0;
        this.music = this.sound.add('menu_bgm', {mute: false, volume: 1.0, rate: 1, loop: true});
        this.music.play();
        
        this.AVATAR_SCALE = 0.25;
        this.ROOMWIDTH = 1024;
        this.ROOMHEIGHT = 672;

        //config for texts
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

        // this.anims.create({
        //     key: 'pour_milk'
        //     frames: this.anims.generateFrameNumbers('pour_milk', {frames:})
        // })


        this.bg = this.add.image(0, 0, 'kitchenTable').setOrigin(0);

        this.add.image(this.ROOMWIDTH, 0,'temp_bg').setOrigin(0);
        //game.physics.startSystem(Phaser.Physics.ARCADE);
        //this.scoreText=this.add.text(20,20,'SCORE:0', scoreConfig);
        this.cashier=this.physics.add.sprite(config.width/2, config.height/2, 'cake');
        this.cashier.body.immovable =true;
        
        //adding ingredient images
        this.fruit=this.physics.add.image(150 ,50,'chocolate').setInteractive({draggable: true});
        
        this.food=this.physics.add.image(200,50,'strawberry').setInteractive({draggable: true});
        
        this.vanilla=this.physics.add.image(200,50,'cherry').setInteractive({draggable: true});

        this.bp=this.physics.add.image(200,50,'cookie').setInteractive({draggable: true});
        
        this.soda=this.physics.add.image(200,50,'carrot').setInteractive({draggable: true});
        
        this.salt=this.physics.add.image(200,50,'candle').setInteractive({draggable: true});
                
        this.fruit.setVelocity(Phaser.Math.Between(0, 500),Phaser.Math.Between(0, 300));
        this.fruit.setBounce(1,1);
        this.fruit.setCollideWorldBounds(true);
        
        this.food.setVelocity(Phaser.Math.Between(0, 500),Phaser.Math.Between(0, 300));
        this.food.setBounce(1,1);
        this.food.setCollideWorldBounds(true);

        this.vanilla.setVelocity(Phaser.Math.Between(0, 500),Phaser.Math.Between(0, 300));
        this.vanilla.setBounce(1,1);
        this.vanilla.setCollideWorldBounds(true);

        this.bp.setVelocity(Phaser.Math.Between(0, 500),Phaser.Math.Between(0, 300));
        this.bp.setBounce(1,1);
        this.bp.setCollideWorldBounds(true);

        this.soda.setVelocity(Phaser.Math.Between(0, 500),Phaser.Math.Between(0, 300));
        this.soda.setBounce(1,1);
        this.soda.setCollideWorldBounds(true);

        this.salt.setVelocity(Phaser.Math.Between(0, 500),Phaser.Math.Between(0, 300));
        this.salt.setBounce(1,1);
        this.salt.setCollideWorldBounds(true);

        

        //animation
        // this.anims.create({
        //     key: 'milk',
        //     frames: this.anims.generateFrameNumbers('milk', {frames: [0, 1, 2, 3]}),
        //     framerate: 8,
        //     repeat: 0
        // });

        // this.anims.create({
        //     key: 'egg',
        //     frames: this.anims.generateFrameNumbers('egg', {frames: [0, 1, 2]}),
        //     framerate: 6,
        //     repeat: 0
        // });


    //this.input.setDraggable(this.fruit);

    //  The pointer has to move 16 pixels before it's considered as a drag
    //this.input.dragDistanceThreshold = 16;

    this.input.on('dragstart', function (pointer, gameObject) {

        gameObject.setVelocity(0,0);

    });

    this.input.on('drag', function (pointer, gameObject, dragX, dragY) {

        gameObject.x = dragX;
        gameObject.y = dragY;

    });

    this.input.on('dragend', function (pointer, gameObject) {

        gameObject.setVelocity(Phaser.Math.Between(0, 500),Phaser.Math.Between(0, 500));

    });
        //this.physics.add.existing(this.fruit);
        //this.physics.add.existing(this.cashier);
        //this.physics.add.existing(this.food);

        //this.fruit.body.setCollideWorldBounds(true);
        this.physics.add.collider(this.fruit,this.cashier);
        this.physics.add.collider(this.food,this.cashier);
        this.physics.add.collider(this.salt,this.cashier);
        this.physics.add.collider(this.vanilla,this.cashier);
        this.physics.add.collider(this.bp,this.cashier);
        this.physics.add.collider(this.soda,this.cashier);
        
        
        

        keySPACE = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.SPACE);
        keyZ = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.Z);

        

        this.add.text(200,150, 'drag and drop the ingredients.',scoreConfig);

        
        //this.cashier=this.add.image(0,0,'character');

        //this.physics.add.overlap(this.fruit,this.cashier);
        this.time = data;
        scoreConfig.color = '#FFFF00';
        this.currentTime = this.add.text(20, 20, this.time, scoreConfig);
        //this.physics.add.overlap(this.fruit,this.cashier);
        
        
    }

    
    

    update(time, delta){

        this.time += delta;
        this.currentTime.text = (this.time/1000).toFixed(2);

        this.physics.add.overlap(this.fruit, this.cashier, function (fruit, cashier) {
            
            //cashier.destroy();
           // console.log(this._fruit); 
           this.count++;
           //this.fruit.destroy();
           //this._fruit=true;
           fruit.setVelocity(0,0);
           this.fruit.destroy();
           this.fruit= this.add.image(config.width/2, config.height/2+10 , "chocolate");
           
        }, null, this);

        this.physics.add.overlap(this.food, this.cashier, function (food, cashier) {
            
            //cashier.destroy();
            this.count++;
            //this.food.anims.play('milk');
           //this.scoreText.setText('SCORE:'+this.count);
           this.food.destroy();
           //this.food.setVelocity(0,0);
           this.add.image(config.width/2-20, config.height/2+20, "strawberry");
           
        }, null, this);

        this.physics.add.overlap(this.salt, this.cashier, function (salt, cashier) {
            
            //cashier.destroy();
            this.count++;
         //  this.scoreText.setText('SCORE:'+this.count);
           
           this.salt.destroy();
           this.add.image(config.width/2, config.height/2-60 , "candle");
        }, null, this);

        this.physics.add.overlap(this.bp, this.cashier, function (bp, cashier) {
            
            //cashier.destroy();
            this.count++;
         //  this.scoreText.setText('SCORE:'+this.count);
           
           this.bp.destroy();
           this.add.image(config.width/2+30, config.height/2-30, "cookie");
        }, null, this);

        this.physics.add.overlap(this.soda, this.cashier, function (soda, cashier) {
            
            //cashier.destroy();
            this.count++;
           //this.scoreText.setText('SCORE:'+this.count);
           
           this.soda.destroy();
           this.add.image(config.width/2+30, config.height/2, "carrot");
        }, null, this);

        this.physics.add.overlap(this.vanilla, this.cashier, function (vanilla, cashier) {
            
            //cashier.destroy();
            this.count++;
          // this.scoreText.setText('SCORE:'+this.count);
           
           this.vanilla.destroy();
           this.add.image(config.width/2-30, config.height/2-30, "cherry");
        }, null, this);


        if(this.count == 6){
            this.music.stop();
            this.scene.start('gradeScene', this.time);
        }
    }
    reset(){
        this.fruit.x=100;
        this.fruit.y=50;
    }
}
