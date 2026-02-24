#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "S23";
const char* password = "passward";

ESP8266WebServer server(80);

#define BUTTON D3
#define LED D5

bool ledState = false;

// ===== HTML page =====
String webpage = R"====(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Krishi Upajh</title>

    <link rel="stylesheet" href="style.css" />

    <!-- fonts  -->
    <link rel="preconnect" href="https://fonts.googleapis.com" />
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin />
    <link
      href="https://fonts.googleapis.com/css2?family=Google+Sans:ital,opsz,wght@0,17..18,400..700;1,17..18,400..700&family=Montserrat:ital,wght@0,100..900;1,100..900&family=Poppins:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;0,900;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800;1,900&display=swap"
      rel="stylesheet"
    />
    <!-- ===== -->

    <!-- Icons  -->
    <link
      rel="stylesheet"
      href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/7.0.1/css/all.min.css"
    />

    <!-- ===== -->

    <style>
      * {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
      }
      body {
        width: 100%;
        height: 100%;
        background-color: #f3f4f9;
        overflow: hidden;
      }

      /* div {
  background-color: greenyellow;
} */
      /* ================================= Header ========================== */

      header {
        background-color: white;
        display: flex;
        justify-content: space-between;
        width: 100%;
        padding: 2px 40px 7px 30px;
        display: flex;
        align-items: center;
        justify-content: space-between;
        box-shadow: -8px -6px 16px 1px;
      }

      header div {
        display: flex;
        flex-direction: column;
        justify-content: center;
        transition-duration: 0.2s;
      }
      header div:hover {
        color: black;
      }
      .logo {
        padding: 2px 10px 2px 10px;
        font-family: "Google Sans", sans-serif;
        font-weight: bold;
        font-size: 30px;
        cursor: pointer;
        color: #2f9712;
        background-color: #0fca51;
        border-radius: 10px;
        color: white;
      }

      .user_name {
        padding: 2px 10px 2px 10px;
        font-family: "Poppins", sans-serif;
        font-weight: 550;
        font-size: 20px;
        cursor: pointer;
        color: #585858;
      }

      .battery {
        padding: 2px 10px 2px 10px;
        font-family: "Poppins", sans-serif;
        font-weight: 550;
        font-size: 14px;
        flex-direction: row;
        justify-content: center;
        align-items: center;
        cursor: pointer;
        color: #585858;
      }
      .battery i {
        rotate: -90deg;
        font-size: 16px;
      }
      .pump {
        padding: 2px 10px 2px 10px;
        font-family: "Poppins", sans-serif;
        height: 50px;
        width: 50px;
        border-radius: 50%;
        display: flex;
        justify-content: center;
        align-items: center;
        border: 1px solid green;
        padding: 10px;
      }
      .pump a {
        text-decoration: none;
        color: black;
        font-weight: 500;
        font-size: 12px;
      }

      .profile {
        padding: 2px 10px 2px 10px;
        font-family: "Poppins", sans-serif;
        font-weight: 600;
        display: flex;
        justify-content: center;
        align-items: center;
        height: 40px;
        width: 40px;
        cursor: pointer;
        border: 2px solid brown;
        border-radius: 50%;
      }

      /* ============================================================== */

      /* ============================ Main ================================= */
      main {
        /* border: 2px solid red; */
        margin-block: 20px;
        height: 100%;
        width: 100%;
        padding: 8px;
      }
      .upper_box {
        display: flex;
        justify-content: space-around;
        align-items: center;
        margin-top: 20px;
        min-height: 150px;
      }
      .lower_box {
        display: flex;
        justify-content: space-around;
        align-items: center;
        margin-top: 50px;
        min-height: 150px;
      }
      .card {
        background-color: white;
        width: 20%;
        padding-top: 20px;
        display: flex;
        flex-direction: column;
        justify-content: space-around;
        font-family: "Poppins", sans-serif;
        align-items: center;
        border-radius: 10px;
        box-shadow: 1px 1px 6px -3px;
      }
      .card p {
        font-family: "Poppins", sans-serif;
        font-size: 25px;
        font-weight: 500;
        color: #585858;
      }

      .display {
        display: flex;
        justify-content: center;
        align-items: center;
        padding: 20px;
      }
      .display .value {
        font-size: 50px;
        padding: 10px;
      }
      .display .unit {
        font-size: 20px;
        font-weight: 600;
        color: black;
      }
      /* ======================================================================= */
    </style>
  </head>


  <body>
    <!-- ========================= Header ============================ -->
    <header>
      <div class="logo">कृषि उपज</div>
      <div class="user_name">Sanju Bhai</div>
      <div class="battery"><i class="fa-solid fa-battery-half"></i>78%</div>
      <div class="pump"><a href="/led">Pump</a></div>
      <div class="profile">P</div>
    </header>
    <!-- ==================================================================== -->

    <!-- =========================== main ========================= -->

    <main>
      <div class="upper_box">
        <div class="card">
          <p>Temperature</p>
          <div class="display">
            <div class="value">35</div>
            <div class="unit"><sup>o</sup>C</div>
          </div>
        </div>

        <div class="card">
          <p>Humidity</p>
          <div class="display">
            <div class="value">25</div>
            <div class="unit">%</div>
          </div>
        </div>

        <div class="card">
          <p>Wind</p>
          <div class="display">
            <div class="value">6</div>
            <div class="unit">Km/h</div>
          </div>
        </div>

        <div class="card">
          <p>Crop</p>
          <div class="display">
            <div class="value">Rice</div>
            <!-- <div class="unit"><sup>o</sup>C</div> -->
          </div>
        </div>
      </div>

      <div class="lower_box">
        <div class="card">
          <p>Moisture</p>
          <div class="display">
            <div class="value" id="moisture">25</div>
            <div class="unit">%</div>
          </div>
        </div>

        <div class="card">
          <p>Nitrogen</p>
          <div class="display">
            <div class="value">5</div>
            <div class="unit">%</div>
          </div>
        </div>

        <div class="card">
          <p>Phosphorus</p>
          <div class="display">
            <div class="value">0.5</div>
            <div class="unit">%</div>
          </div>
        </div>

        <div class="card">
          <p>Potassium</p>
          <div class="display">
            <div class="value">4</div>
            <div class="unit">%</div>
          </div>
        </div>
      </div>
    </main>
    <!-- ==================================================== -->
     <script>
      setInterval(function () {
        fetch("/moisture")
          .then((r) => r.text())
          .then((data) => {
            document.getElementById("moisture").innerHTML = data;
          });
      }, 200);
    </script>
  </body>
  
</html>

)====";

// ===== handlers =====

void handleRoot() {
  server.send(200, "text/html", webpage);
}

void handleButton() {
  int a = analogRead(A0);
  a = map(a, 300, 900, 100, 0);
  server.send(200, "text/plain", (String)a);
}

void handleLED() {
  ledState = !ledState;
  digitalWrite(LED, ledState);
  server.sendHeader("Location", "/");  // redirect back
  server.send(303);
}

// ===== setup =====

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/moisture", handleButton);
  server.on("/led", handleLED);

  server.begin();
}

void loop() {
  server.handleClient();
}
