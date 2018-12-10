#include "mainUI.h"
#include <iostream>
#include <QVariant>
#include <QString>
#include <tcpUserSocket.h>

cs457::tcpUserSocket *socketSender;

mainUI::mainUI(QObject* qObjectPointer,cs457::tcpUserSocket *Setsocket)
{
    mainUI::mainWindow = qObjectPointer;
    socketSender =Setsocket;
}

void mainUI::testSlots(const std::string *newText ) {
    QVariant qVariant(newText->c_str());
    QObject* outputArea = mainUI::mainWindow->findChild<QObject*>("outputArea");
    outputArea->setProperty("text", qVariant);
    delete (newText);
}

void mainUI::getCommand(const QString &command){
    string comString = command.toStdString();
    if(comString.size() >0){


    if(comString.at(0) == '/'){
        socketSender->sendString(comString.substr(1,comString.size()));
    }
    else if(selectedChannel != ""){
        comString = "privmsg " + selectedChannel + " :" + comString;
        socketSender->sendString(comString);
    }
    else{
        QObject* outputArea = mainUI::mainWindow->findChild<QObject*>("outputArea");
        std::string helpText = "use /Join channel to join a channel or /Help for a list of commands \n";
        string currentText = outputArea->property("text").toString().toStdString();
        std::string *updated = new string(currentText + "\n" + helpText);
        outputArea->setProperty("text",QVariant(updated->c_str()));

    }
    }

}

void mainUI::setChannelName(const std::string *newChannel, int numChannels){
    QVariant qVariant(newChannel->c_str());
    std::string chan = "Channel";
    chan += to_string(numChannels);
    QObject* button = mainUI::mainWindow->findChild<QObject*>(chan.c_str());
    QObject* channelNameText = mainUI::mainWindow->findChild<QObject*>("channelTitle");
    selectedChannel = *newChannel;
    button->setProperty("text",qVariant);
    channelNameText->setProperty("text", qVariant);
    delete (newChannel);
}
