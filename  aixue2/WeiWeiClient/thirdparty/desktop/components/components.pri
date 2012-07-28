QML_FILES = \
            $$PWD/qmldir \
            $$PWD/Label.qml \
            $$PWD/Button.qml \
            $$PWD/ComboBox.qml \
            $$PWD/Dial.qml \
            $$PWD/Dialog.qml \
            $$PWD/ProgressBar.qml \
            $$PWD/ScrollBar.qml \
            $$PWD/Switch.qml \
            $$PWD/TableView.qml \
            $$PWD/ToolBar.qml \
            $$PWD/ButtonRow.qml \
            $$PWD/ButtonColumn.qml \
            $$PWD/Frame.qml \
            $$PWD/MenuItem.qml   \
            $$PWD/Slider.qml \
            $$PWD/TabBar.qml \
            $$PWD/Tab.qml \
            $$PWD/ToolButton.qml \
            $$PWD/CheckBox.qml \
            $$PWD/ContextMenu.qml \
            $$PWD/GroupBox.qml \
            $$PWD/RadioButton.qml \
            $$PWD/SpinBox.qml \
            $$PWD/TabFrame.qml \
            $$PWD/TextArea.qml \
            $$PWD/ScrollArea.qml \
            $$PWD/SplitterRow.qml \
            $$PWD/SplitterColumn.qml \
            $$PWD/StatusBar.qml \
            $$PWD/TableColumn.qml \
            $$PWD/TextField.qml \
            $$PWD/ApplicationWindow.qml

QML_DIRS = \
        $$PWD/custom \
        $$PWD/private \
        $$PWD/images
qmlfiles.files = $$QML_FILES
qmlfiles.sources = $$QML_FILES
#qmlfiles.path = $$INSTALL_IMPORTS/$$TARGETPATH

qmldirs.files = $$QML_DIRS
qmldirs.sources = $$QML_DIRS
#qmldirs.path = $$INSTALL_IMPORTS/$$TARGETPATH

INSTALLS += qmlfiles qmldirs
