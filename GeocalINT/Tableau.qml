import QtQuick 2.3
import QtQuick.Controls 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11


TableView{
    anchors.fill: parent
    TableViewColumn {
        role: "svid"
        title: "SVID"
        width: parent.width/23
    }
    TableViewColumn {
        role: "iodc"
        title: "IODC"
        width: parent.width/23
    }
    TableViewColumn {
        role: "tgd"
        title: "TGD"
        width: parent.width/23
    }
    TableViewColumn {
        role: "toc"
        title: "TOC"
        width: parent.width/23
    }
    TableViewColumn {
        role: "af0"
        title: "AF0"
        width: parent.width/23
    }
    TableViewColumn {
        role: "af1"
        title: "AF1"
        width: parent.width/23
    }
    TableViewColumn {
        role: "af2"
        title: "AF2"
        width: parent.width/23
    }
    TableViewColumn {
        role: "iode"
        title: "IODE"
        width: parent.width/23
    }
    TableViewColumn {
        role: "crs"
        title: "CRS"
        width: parent.width/23
    }
    TableViewColumn {
        role: "dn"
        title: "DN"
        width: parent.width/23
    }
    TableViewColumn {
        role: "m0"
        title: "M0"
        width: parent.width/23
    }
    TableViewColumn {
        role: "cuc"
        title: "CUC"
        width: parent.width/23
    }
    TableViewColumn {
        role: "e"
        title: "E"
        width: parent.width/23
    }
    TableViewColumn {
        role: "sqrtA"
        title: "SQRT(A)"
        width: parent.width/23
    }
    TableViewColumn {
        role: "toe"
        title: "TOE"
        width: parent.width/23
    }
    TableViewColumn {
        role: "fit"
        title: "FIT"
        width: parent.width/23
    }
    TableViewColumn {
        role: "cic"
        title: "CIC"
        width: parent.width/23
    }
    TableViewColumn {
        role: "omega0"
        title: "Omega0"
        width: parent.width/23
    }
    TableViewColumn {
        role: "i0"
        title: "I0"
        width: parent.width/23
    }
    TableViewColumn {
        role: "crc"
        title: "CRC"
        width: parent.width/23
    }
    TableViewColumn {
        role: "omega"
        title: "Omega"
        width: parent.width/23
    }
    TableViewColumn {
        role: "omegap"
        title: "OmegaP"
        width: parent.width/23
    }
    TableViewColumn {
        role: "idot"
        title: "IDOT"
        width: parent.width/23
    }
}
