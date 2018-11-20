// Conexao WAMP com o Roteador
var conexao = new autobahn.Connection({
    transports: [
        {
            'type': 'websocket',
            'url' : 'ws:' + '//' + document.location.host + '/ws'
        }
    ],
    realm: "embarcados"
});

conexao.onopen = function (sessao, detalhe) {
    main(sessao);
};

conexao.onclose = function (razao, detalhe) {
    console.log("Conexão perdida: " + razao);
};

// Iniciar conexao
conexao.open();

function main(sessao) {
    sessao.subscribe("io.crossbar.demo.voto.onvoto",
            function (msg) {
                var data = JSON.parse(msg);
                for (key in data) {
                    document.getElementById("votos" + key).value = data[key];
                }
            });

    // Obtem votacao
    sessao.call("io.crossbar.demo.voto.get").then(
            function (msg) {
                atualizaLabel(msg);
            });

    // subscribe reset de votacao
    sessao.subscribe("io.crossbar.demo.voto.onreset",
            function (msg) {
                atualizaLabel(msg);
            });

    // Evento pressionar botao reset
    document.getElementById("resetVotos").onclick =
            function () {
                sessao.call("io.crossbar.demo.voto.reset");
            };

    // Evento pressionar botoes votacao
    var btnVotos = document.getElementById("votoContainer").getElementsByTagName("button");
    for (var i = 0; i < btnVotos.length; i++) {
        btnVotos[i].onclick =
                function (evt) {
                    sessao.call("io.crossbar.demo.voto.votar", [evt.target.id]);
                };
    }
}

function atualizaLabel(msg) {
    var data = JSON.parse(msg);
    for (var info in data) {
        var dataCopia = data[info];
        for (data in dataCopia) {
            var mainData = dataCopia[data];
            for (key in mainData) {
                document.getElementById("votos" + key).value = mainData[key];
            }
        }
    }
}


