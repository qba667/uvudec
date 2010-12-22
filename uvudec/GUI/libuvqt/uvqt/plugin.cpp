#include "uvqt/hexdump.h"
#include "uvqt/plugin.h"
#include "uvd/util/util.h"

#include <QtPlugin>

UVQtPlugin::UVQtPlugin(QObject *parent)
		: QObject(parent)
{
	printf("constructor\n");
	m_widgets.append(new UVQtPlugin1(this));
	m_widgets.append(new UVQtPlugin2(this));
}

QList<QDesignerCustomWidgetInterface*> UVQtPlugin::customWidgets() const
{
	return m_widgets;
}

/*
UVQtPlugin1
*/

UVQtPlugin1::UVQtPlugin1(QObject *parent)
    : QObject(parent)
{
	std::vector<std::string> the_split = UVDSplit("blah blah blah", ' ', true);
	printf("split items: %d\n", the_split.size());

    initialized = false;
}

void UVQtPlugin1::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool UVQtPlugin1::isInitialized() const
{
    return initialized;
}

QWidget *UVQtPlugin1::createWidget(QWidget *parent)
{
    return new UVQtScrollableHexdump(parent);
}

QString UVQtPlugin1::name() const
{
    return "UVQtScrollableHexdump";
}

QString UVQtPlugin1::group() const
{
    return "UVNet";
}

QIcon UVQtPlugin1::icon() const
{
    return QIcon();
}

QString UVQtPlugin1::toolTip() const
{
    return "";
}

QString UVQtPlugin1::whatsThis() const
{
    return "";
}

bool UVQtPlugin1::isContainer() const
{
    return false;
}

QString UVQtPlugin1::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"UVQtScrollableHexdump\" name=\"scrollableHexdump\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>300</width>\n"
           "    <height>100</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"toolTip\" >\n"
           "   <string>Binary hexdump</string>\n"
           "  </property>\n"
           "  <property name=\"whatsThis\" >\n"
           "   <string>Hexdump displays hexidecimal and ASCII of a binary.</string>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString UVQtPlugin1::includeFile() const
{
    return "uvdqt/hexdump.h";
}

//Q_EXPORT_PLUGIN2(customwidgetplugin, UVQtPlugin1)
Q_EXPORT_PLUGIN2(customwidgetsplugin, UVQtPlugin)

