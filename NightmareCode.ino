#include <Servo.h>

Servo monster;
Servo robot;
Servo knockerOverer;
Servo sleepy;
Servo hint;

int lantern = 8;

bool hasItems = false;
bool notDead = true;
int robotHealth = 2;
int robotSpot = 0;
int lastSpot;
int lastSpotHit;
float robotChooseTimer = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));
  monster.attach(11);
  robot.attach(13);
  knockerOverer.attach(10);
  knockerOverer.write(135);
  monster.write(0);

  pinMode(lantern, OUTPUT);
  sleepy.attach(12);
  sleepy.write(0);
  digitalWrite(lantern, HIGH);

  hint.attach(9);
  hint.write(90);

  pinMode(3, INPUT);
  pinMode(2, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
}

void loop() {
  // Toggles sleeping man and light
  sleepyGuy();

  int monsterSpot = digitalRead(2);
  int itemCheck = digitalRead(3);  //Original Steak Sauce (sorry I had to)


  if (notDead) {
    int robotSpotLeft = digitalRead(7);
    int robotSpotMiddle = digitalRead(6);
    int robotSpotRight = digitalRead(5);

    if(robotSpotRight > 0){Serial.print("right");}

    //Check if player is on correct location
    if (robotSpotLeft > 0 && robotSpot == 2) {
      robotHealth--;
      lastSpotHit = robotSpot;
      shakeRobot(145);
    }
    if (robotSpotRight > 0 && robotSpot == 0) {
      robotHealth--;
      lastSpotHit = robotSpot;
      shakeRobot(45);
    }
    if (robotSpotMiddle > 0 && robotSpot == 1) {
      robotHealth--;
      lastSpotHit = robotSpot;
      shakeRobot(90);
    }
    delay(500);

    //Choose new location
    if (robotChooseTimer <= 0) {
      lastSpot = robotSpot;
      robotChooseTimer = 0.1;
      while (robotSpot == lastSpot) {
        robotSpot = random(0, 3);
        if (robotSpot == lastSpotHit) {
          robotSpot = random(0, 3);
        }
      }
    } else {
      robotChooseTimer--;
    }

    if (robotHealth > 0) {
      switch (robotSpot) {
        case 0: robot.write(45); break;
        case 1: robot.write(90); break;
        case 2: robot.write(145); break;
      }
    }
    if (robotHealth <= 0 && notDead) {
      robot.write(15);
      delay(500);
      robot.write(165);
      notDead = false;
      robotSpot = -1;
    }


    delay(1500);
  }  


  if (itemCheck > 0) {
    hasItems = true;
  }

  if (monsterSpot > 0 && hasItems) {
    monster.write(180);
    delay(50000);
  } else if (monsterSpot > 0) {
    knockerOverer.write(0);
    delay(200);
    knockerOverer.write(135);

    hint.write(0);
  } else {
    knockerOverer.write(135);
  }

}

void shakeRobot(int initialDegree) {
  for (int i = 0; i < 5; i++) {
    robot.write(initialDegree + 10);
    delay(250);
    robot.write(initialDegree - 10);
    delay(250);
  }
}

void sleepyGuy() {
  digitalWrite(lantern, LOW);
  sleepy.write(50);
  delay(1000);

  digitalWrite(lantern, HIGH);
  sleepy.write(0);
  if(notDead){
    delay(500);
  } else{
    delay(3000);
  }
}