import processing.serial.*;

Serial myPort;
String ledColor;
boolean barrierOpen = false;
boolean[] parkingSpaces = new boolean[4]; // Array to track occupied parking spaces

void setup() {
  size(400, 300);
  myPort = new Serial(this, "COM6", 9600);
}

void draw() {
  background(255);
  drawParkingSpaces();
  drawBarrier();
  drawSemaphore();

  if (myPort.available() > 0) {
    String sensorInput = myPort.readStringUntil('\n');
    if (sensorInput != null) {
      handleSensorInput(sensorInput.trim());
    }
  }
}

void drawParkingSpaces() {
  for (int i = 0; i < 4; i++) {
    rect(20 + i * 70, 200, 50, 80);
    if (parkingSpaces[i]) {
      drawX(20 + i * 70, 200);
    }
  }
}

void drawX(int x, int y) {
  line(x, y, x + 50, y + 80);
  line(x + 50, y, x, y + 80);
}

//void handleSensorInput(String input) {
//  if (input.equals("Sensor1Detected")) {
//    addRandomX();
//  } else if (input.equals("Sensor2Detected")) {
//    removeRandomX();
//  }
//}

void addRandomX() {
  ArrayList<Integer> availableSpaces = new ArrayList<Integer>();
  for (int i = 0; i < parkingSpaces.length; i++) {
    if (!parkingSpaces[i]) {
      availableSpaces.add(i);
    }
  }
  if (!availableSpaces.isEmpty()) {
    int randomIndex = (int) random(availableSpaces.size());
    parkingSpaces[availableSpaces.get(randomIndex)] = true;
  }
}

void removeRandomX() {
  ArrayList<Integer> occupiedSpaces = new ArrayList<Integer>();
  for (int i = 0; i < parkingSpaces.length; i++) {
    if (parkingSpaces[i]) {
      occupiedSpaces.add(i);
    }
  }
  if (!occupiedSpaces.isEmpty()) {
    int randomIndex = (int) random(occupiedSpaces.size());
    parkingSpaces[occupiedSpaces.get(randomIndex)] = false;
  }
}


void drawBarrier() {
  // Drawing the barrier
  stroke(0);
  strokeWeight(4);
  line(300, 150, 300, 200); // Barrier stand
  if (barrierOpen) {
    line(300, 150, 400, 150); // Open barrier
  } else {
    line(300, 150, 300, 50); // Closed barrier
  }
}

void drawSemaphore() {
  // Drawing semaphore
  float circleDiameter = 20; // Diameter of the semaphore light

  // Position of the semaphore
  float semaphoreX = 365;
  float semaphoreY = 60;

  fill(0); // Black color for the semaphore base
  rect(350, 20, 30, 80); // Drawing the semaphore base

  if (ledColor != null) {
    if (ledColor.trim().equals("Green")) {
      fill(0, 255, 0); // Green light
    } else if (ledColor.trim().equals("Red")) {
      fill(255, 0, 0); // Red light
    } else {
      fill(100); // Default light color when status is not green or red
    }
  } else {
    fill(100); // Default light color when ledColor is null
  }

  ellipse(semaphoreX, semaphoreY, circleDiameter, circleDiameter); // Draw the semaphore light
}


void updateStatus(String status) {
  switch (status) {
    case "Green":
      barrierOpen = true;
      break;
    case "Red":
      barrierOpen = false;
      break;
  }
}

  void handleSensorInput(String input) {
  if (input.equals("Sensor1Detected")) {
    addRandomX();
  } else if (input.equals("Sensor2Detected")) {
    removeRandomX();
  } else if (input.equals("Green") || input.equals("Red")) {
    ledColor = input;
    updateStatus(ledColor);
  }
}
