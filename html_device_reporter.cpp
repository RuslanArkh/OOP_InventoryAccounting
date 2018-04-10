#include "html_device_reporter.h"
#include "computer.h"
#include "embedded_gsm.h"
#include "mobile_phone.h"
#include "server_computer.h"
#include "my_utility.h"

const std::string HTMLDeviceReporter::_header{
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<head>\n"
        "\t<title>Inventory accounting</title>\n"
        "\t<link rel='stylesheet' href='style.css'>\n"
    "</head>\n"
    "<body>\n"
    "<div id='device_list'>\n"
};

const std::string HTMLDeviceReporter::_footer{
    "</div>\n"
    "</body>\n"
    "</html>\n"
};

HTMLDeviceReporter::HTMLDeviceReporter(const std::string & _fileName)
    : DeviceReporter(_fileName), _content{} {}

HTMLDeviceReporter::~HTMLDeviceReporter() {  }


std::string HTMLDeviceReporter::defaultDeviceData(const InventoryDevice * _d, int indent) const {
    std::ostringstream default_data;
    int temp_indent = indent;
    while(temp_indent-- > 0)
        default_data << "\t";
    temp_indent = indent;
    default_data << "<span class='id'>" << _d->GetId() << "</span>\n";
    while(temp_indent-- > 0)
        default_data << "\t";
    default_data << "<span class='date'>" << _d->GetDate() << "</span>\n";
    return default_data.str();
}

std::string HTMLDeviceReporter::GSMData(const GSMDevice * _d, int indent) const {
    std::ostringstream gsm_data;
    int temp_indent = indent;
    while(temp_indent-- > 0)
        gsm_data << "\t";
    temp_indent = indent;
    gsm_data << "<div class='gsm_data'>\n";
    while(temp_indent-- > 0)
        gsm_data << "\t";
    temp_indent = indent;
    gsm_data << "\t<span class='number'>Account number: " << _d->GetAccountNumber() + "</span>\n";
    const std::vector<int> & _freqs = _d->GetFrequencies();
    if (_freqs.size() > 0) {
        while(temp_indent-- > 0)
            gsm_data << "\t";
        temp_indent = indent;
        gsm_data << "\t<div class='frequencies_accordion' onClick=''>Frequencies:\n" << "\t\t\t\t<ul>\n";
        for (int _freq: _freqs) {
            while(temp_indent-- > 0)
                gsm_data << "\t";
            temp_indent = indent;
            gsm_data << "\t\t\t<li>" << _freq << "</li>\n";
        }
        while(temp_indent-- > 0)
            gsm_data << "\t";
        temp_indent = indent;
        gsm_data << "\t\t</ul>\n";
    }
    while(temp_indent-- > 0)
        gsm_data << "\t";
    temp_indent = indent;
    gsm_data << "\t</div>\n";
    while(temp_indent-- > 0)
        gsm_data << "\t";
    temp_indent = indent;
    gsm_data << "</div>\n";
    return gsm_data.str();
}

void HTMLDeviceReporter::add_device(const Computer * _d) {
    _content << "\t<div class='" << MyUtility::toLower(_d->type()) << "'>\n" <<
            defaultDeviceData(_d, 2) <<
            "\t\t<div class='specific_data'>\n" <<
            "\t\t\t<span class='disk_memory'>Disk memory: " << _d->GetDiskMemory() << " Gb</span>\n" <<
            "\t\t\t<span class='processor_model'>Processor model: " <<
                                                 _d->GetProcessorModel() << "</span>\n" <<
            "\t\t\t<span class='ram'>RAM: " << _d->GetRAM() << " Mb</span>\n" <<
            "\t\t</div>\n" <<
            "\t</div>\n";

}

void HTMLDeviceReporter::add_device(const EmbeddedGSM * _d) {
    _content << "\t<div class='" << MyUtility::toLower(_d->type()) << "'>\n" <<
            defaultDeviceData(_d, 2) <<
            "\t\t<div class='specific_data'>\n" <<
            "\t\t\t<span class='disk_memory'>" << _d->GetClockFrequency() << "</span>\n" <<
            "\t\t</div>\n" <<
            GSMData(_d, 2) <<
            "\t</div>\n";
}

void HTMLDeviceReporter::add_device(const MobilePhone * _d) {
    _content << "\t<div class='" << MyUtility::toLower(_d->type()) << "'>\n" <<
            defaultDeviceData(_d, 2) <<
            "\t\t<div class='specific_data'>\n" <<
            "\t\t\t<span class='manufacturer'>Manufacturer: " <<
                                            _d->GetManufacturerTitle() << "</span>\n" <<
            "\t\t\t<span class='model_title'>Model: " << _d->GetModelTitle() << "</span>\n" <<
            "\t\t</div>\n" <<
            GSMData(_d, 2) <<
            "\t</div>\n";
}

void HTMLDeviceReporter::add_device(const ServerComputer * _d) {
    _content << "\t<div class='" << MyUtility::toLower(_d->type()) << "'>\n" <<
            defaultDeviceData(_d, 2) <<
            "\t\t<div class='specific_data'>\n" <<
            "\t\t\t<span class='hpp_replication'>" << _d->GetHDDReplication() << "</span>\n";
    const std::vector<std::string> & temp_ids = _d->GetIds();
    if (temp_ids.size() > 0) {
        _content << "\t\t\t<div class='ids_list_accordion'>\n\t\t\t<ul>\n";
        for (const std::string & str: temp_ids)
            _content << "\t\t\t\t<li>" << str << "</li>\n";
        _content << "\t\t\t</ul>\n\t\t\t</div>\n";
    }
    _content << "\t\t</div>\n\t</div>\n";
}

void HTMLDeviceReporter::MakeReport() {
    outputFile->open(FileName, std::ios_base::out | std::ios_base::trunc);
    *outputFile << _header << _content.str() << _footer;
    _content.clear();
    _content.str("");
    outputFile->close();
}
