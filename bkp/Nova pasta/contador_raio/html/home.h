const char home_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Web Server</title>
    <link rel="stylesheet" type="text/css" href="/style.css">
    <script>@HOME_SCRIPT@</script>
</head>

<body>
    <div class="container1">
        <h1>MANHATTAN</h1>
    </div>
    <div class="container1">
        <div class="container2">

            <div class="container1">
                <label>Nome:</label>
            </div>
            <div class="container1">
                <label>Rede:</label>
            </div>
            <div class="container1">
                <label>Senha:</label>
            </div>
            <div class="container1">
                <label>Api:</label>
            </div>

        </div>
        <div class="container2">

            <form action="/enviar_parametros" method="POST" target="hidden_iframe">
                <input class="placeholder_style" type="text" id="nome"><br>
                <input class="placeholder_style" type="text" id="rede"><br>
                <input class="placeholder_style" type="text" id="senha"><br>
                <input class="placeholder_style" type="text" id="api"><br>
                <input class="bt_style" type="submit" value="SALVAR PARAMETROS">
                <button onclick="fetch('/reset_esp')">RESET</button>
            </form>
            <iframe name="hidden_iframe" style="display:none;"></iframe>
        </div>

    </div>

</body>
</html>
)rawliteral";

const char HOME_SCRIPT[] PROGMEM = R"rawliteral(

    window.onload = function() {
        fetch('/label_att')
            .then(response => response.json())
            .then(data => {
                document.getElementById('nome').value = data.nome;
                document.getElementById('rede').value = data.rede;
                document.getElementById('senha').value = data.senha;
                document.getElementById('api').value = data.api;
            })
            .catch(error => console.error('Erro:', error));
    };

)rawliteral";

