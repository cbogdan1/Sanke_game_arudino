  #include <Wire.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>

  //joystick
  int xPin =A0;
  int yPin =A1;
  int buttonPin=2;
  int xVal;
  int yVal;
  int button_state;


  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 64
  #define OLED_RESET -1

  #define block_length 4
  #define block_width 4
  #define oled_center_x 64
  #define oled_center_y 32
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


  const int x_max_lenght=SCREEN_WIDTH/block_length;
  const int y_max_lenght=SCREEN_HEIGHT/block_width;
  int snakeX[50];
  int snakeY[50];
  int snake_length=3;

  enum dir { right, left, up, down };
  dir current_dirr = right;
  dir next_dir = right;


  int foodX;
  int foodY;
  bool foodExists = false;

  bool gameOver = false;

  void spawn_food() {
    if (!foodExists) {
      foodX = (random(1, (SCREEN_WIDTH / block_length) - 2)) * block_length;
      foodY = (random(1, (SCREEN_HEIGHT / block_width) - 2)) * block_width;
      foodExists = true;
    }
    display.fillRect(foodX, foodY, block_length, block_width, SSD1306_WHITE);
  }
  // snake movement
  void move_right() {
    for (int i = snake_length - 1; i > 0; i--) {
      snakeX[i] = snakeX[i - 1];
      snakeY[i] = snakeY[i - 1];
    }
    snakeX[0] += block_length;
  }
  void move_left() {
    for (int i = snake_length - 1; i > 0; i--) {
      snakeX[i] = snakeX[i - 1];
      snakeY[i] = snakeY[i - 1];
    }
    snakeX[0] -= block_length;
  }
  void move_up() {
    for (int i = snake_length - 1; i > 0; i--) {
      snakeX[i] = snakeX[i - 1];
      snakeY[i] = snakeY[i - 1];
    }
    snakeY[0] -= block_width;
  }
  void move_down() {
    for (int i = snake_length - 1; i > 0; i--) {
      snakeX[i] = snakeX[i - 1];
      snakeY[i] = snakeY[i - 1];
    }
    snakeY[0] += block_width;
  }


  void init_snake(){
    for(int i=0;i<3;i++){
      display.fillRect(snakeX[i], snakeY[i], block_length, block_width,SSD1306_WHITE);
      snakeX[i+1]=snakeX[i]+block_length;
      snakeY[i+1]=snakeY[i];
    }
    for (int i = 0; i < snake_length; i++) {
    display.fillRect(snakeX[i], snakeY[i], block_length, block_width, SSD1306_WHITE);
    }
  }

  void draw_snake(){
    display.clearDisplay();
    display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
    for(int i=0;i<snake_length;i++){
      display.fillRect(snakeX[i], snakeY[i], block_length, block_width,SSD1306_WHITE);
    }
  }
  void detect_col(){
    if (snake_length > 3) {
    for (int i = 1; i < snake_length; i++) {
      if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
        game_over();
        return;
      }
    }
  }
    if (snakeX[0] <= 0 || snakeX[0] + block_length >= SCREEN_WIDTH ||
      snakeY[0] <= 0 || snakeY[0] + block_width >= SCREEN_HEIGHT) {
    game_over();
   }
  }

  void setup() {
    pinMode(xPin,INPUT);
    pinMode(yPin,INPUT);
    pinMode(buttonPin,INPUT_PULLUP);
    display.begin(SSD1306_SWITCHCAPVCC,0x3C); //SSD1306_SWITCHCAPVCC ===> SWITCHCAPVCC sursa de alimentare interna(direct de la arduini)
                                            //SSD1306_EXTERNALVCC   ===> EXTERNALVCC alta sursa externa
                                            // 0x3C adresa disp din comunicarea I2C
    display.clearDisplay();
    display.setTextSize(1);
    display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
    snakeX[0] = oled_center_x - block_length;
    snakeY[0] = oled_center_y - block_width;
    init_snake();
    display.display();
  }
  void run_game(){
    xVal = analogRead(xPin);
    yVal = analogRead(yPin);
    button_state = digitalRead(buttonPin);
      //citire valori de pe joystick
    if (xVal > 700) {
      next_dir = right;
    } else if (xVal < 300) {
      next_dir = left;
    } else if (yVal > 700) {
      next_dir = down;
    } else if (yVal < 300) {
      next_dir = up;
    }

    // if ((current_dirr == right && next_dir == left) ||
    //     (current_dirr == left && next_dir == right) ||
    //     (current_dirr == up && next_dir == down) ||
    //     (current_dirr == down && next_dir == up)) {
    //   next_dir = current_dirr;
    // }   //blocheaza schimbarea left<-->right up<-->down directa dar nu intervine doar blocheaza si nu te lasa sa schimbi
    if(current_dirr == right && next_dir == left){  //dreapta stanga trece sus 
      next_dir = up;
    }
    else if(current_dirr == left && next_dir == right){ //stanga dreapta trece jos
      next_dir= down;
    }
    else if(current_dirr == up && next_dir == down){ //jos sus trece stanga
      next_dir= left;
    }
    else if(current_dirr == down && next_dir == up){ //sus jos trece dreapta
      next_dir= right;
    }

  
    current_dirr = next_dir;
    switch (current_dirr) {
      case right: move_right(); break;
      case left: move_left(); break;
      case up: move_up(); break;
      case down: move_down(); break;
    }

    if (snakeX[0] == foodX && snakeY[0] == foodY) {
      if(snake_length < 50) {
        snake_length++;
      }
      foodExists = false;
    }

    draw_snake();
    spawn_food();
    display.display();
    delay(100);
  }
  void game_over() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 20);
    display.println("GAME OVER");
    display.setTextSize(1); // text normal pentru scor
    display.setCursor(45, 45);
    display.print("Score: ");
    display.print(snake_length - 3);
    display.display();
    gameOver = true;
  }
  void reset_game() {
  gameOver = false;
  snake_length = 3;
  current_dirr = right;
  next_dir = right;

  snakeX[0] = oled_center_x - block_length;
  snakeY[0] = oled_center_y - block_width;
  for (int i = 1; i < snake_length; i++) {
    snakeX[i] = snakeX[i - 1] + block_length;
    snakeY[i] = snakeY[i - 1];
  }

  display.clearDisplay();
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  display.display();
}
void loop() {
  detect_col();

  if (!gameOver) {
    run_game();
  }
  button_state = digitalRead(buttonPin);
  if (gameOver && button_state == LOW) {
    delay(200);
    reset_game();
  }
}
