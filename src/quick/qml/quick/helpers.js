.pragma library

var color = {
    ubuntuOrange: "#DD4814",
    white: "#FFFFFF",
    black: "#000000",
    lightAubergine: "#77216F",
    midAubergine: "#5E2750",
    darkAubergine: "#2C001E",
    warmGray: "#AEA79F",
    coolGray: "#333333",
    smallDotGray: "#AEA79F",
    textGray: "#333333",
    canonicalAubergine: "#772953",
}

function randomColor() {
    var keys = Object.keys(color);
    var i = Math.floor( Math.random()*keys.length );
    return color[keys[i]];
}
