import QtQuick 2.3
import QtQuick.Controls 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11

Item{
    function readValue(carray){
        for (var i=0; i<carray;i++){
            console.log("test",carray[i])
        }
    }
}

