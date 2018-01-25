var url = "../../arduino/digital/8";
//var url = "state.html";
var on = "on";
var off = "off";
var state;
var baseLine;
$(document).ready(function () {
    checkStatus();
    setInterval(function () {
        checkStatus();
    }, 5000);


    $(".btn").on("click", function (e) {
        e.preventDefault();
        hitApi($(this).val(), $(this).attr("id"));
    });

    var switchToInput = function () {
        var $input = $("<input>", {
            val: $(this).text(),
            type: "text"
        });
        $input.addClass("loadNum");
        $(this).replaceWith($input);
        $input.on("blur", switchToSpan).on("keyup", function(e){
        if(e.keyCode == 13)
            $(this).blur();
    })  ;
        $input.select();
    };
    var switchToSpan = function () {
        var $span = $("<span>", {
            text: $(this).val()
        });
        $span.addClass("loadNum");
        $(this).replaceWith($span);
        updateBaseLineTemp($(this).val());
        $span.on("dblclick", switchToInput);
    }
    $(".loadNum").on("dblclick", switchToInput)
});


function convertMS(ms) {
    var h, m, s;
    s = Math.floor(ms / 1000);
    m = Math.floor(s / 60);
    h = Math.floor(m / 60);

    s = s % 60;
    m = m % 60;
    h = h % 24;

    h = pad(h, 2);
    s = pad(s, 2);
    m = pad(m, 2);
    return h + ":" + m + ":" + s;
}

function pad(num, size) {
    var s = num + "";
    while (s.length < size) s = "0" + s;
    return s;
}

function parseResponse(msg) {
    var result = $.parseJSON(msg);
    var t = convertMS(result.elapsedTime);
    $("#temperature").text(result.temp.toFixed(2));
    if (result.status == 1) {
        $("#" + on).attr("disabled", true);
        $("#" + off).attr("disabled", false);
        state = on;
    }
    else {
        $("#" + on).attr("disabled", false);
        $("#" + off).attr("disabled", true);
        state = off;
    }
    $("#message").text("Heating is currently switched " + state);
    $("#time").text(t);
    $(".loadNum").text(result.baselineTemp);
    baseLine = result.baselineTemp;
}
function updateBaseLineTemp(newTemp) {
    $.ajax({
        url: "../../arduino/temp/set/" + newTemp,
        type: "GET"
    });
}

function hitApi(param, id) {
    $.ajax({
        url: url + "/" + param,
        type: "GET",
        success: function (data, status, jqXHR) {
            parseResponse(data);
        }
    });
}

function checkStatus() {
    $.ajax({
        url: url,
        type: "GET",
        success: function (data, status, jqXHR) {
            parseResponse(data);
        }
    });
}