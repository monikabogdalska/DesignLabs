#pragma once

#include <string>
#include <exception>
#include <msclr/marshal_cppstd.h> 
#include "serial/serial.h"        
using namespace System::Text::RegularExpressions;
using namespace msclr::interop;


namespace UartWindow {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	
	
	public ref class mainform : public System::Windows::Forms::Form
	{
	private:
		
		serial::Serial* mySerial;

	public:
		mainform(void)
		{
			InitializeComponent();
			mySerial = nullptr; 
			
			chart1->Series[0]->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			chart2->Series[0]->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			chart3->Series[0]->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;

			// 2. Grubosc linii 
			chart1->Series[0]->BorderWidth = 2;
			chart2->Series[0]->BorderWidth = 2;
			chart3->Series[0]->BorderWidth = 2;

			// 3. Kolory
			chart1->Series[0]->Color = Color::Red;
			chart2->Series[0]->Color = Color::Blue;
			chart3->Series[0]->Color = Color::Green;

			// === WYKRES 1 (BOSCH) ===
			chart1->ChartAreas[0]->AxisY->Title = "Temperatura [°C]"; // Oœ pionowa
			chart1->ChartAreas[0]->AxisX->Title = "Numer próbki";          // Oœ pozioma
			
			chart1->ChartAreas[0]->AxisY->TitleFont = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
			chart1->ChartAreas[0]->AxisX->TitleFont = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
			// === WYKRES 2 (CIŒNIENIE) ===
			chart2->ChartAreas[0]->AxisY->Title = "Ciœnienie [Pa]";
			chart2->ChartAreas[0]->AxisX->Title = "Numer próbki";
			chart2->ChartAreas[0]->AxisY->TitleFont = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
			chart2->ChartAreas[0]->AxisX->TitleFont = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);

			// === WYKRES 3 (DS18B20) ===
			chart3->ChartAreas[0]->AxisY->Title = "Temperatura [°C]";
			chart3->ChartAreas[0]->AxisX->Title = "Numer próbki";
			chart3->ChartAreas[0]->AxisY->TitleFont = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
			chart3->ChartAreas[0]->AxisX->TitleFont = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);

			// 4. SKALOWANIE 
			chart1->ChartAreas[0]->AxisY->IsStartedFromZero = false;
			chart2->ChartAreas[0]->AxisY->IsStartedFromZero = false;
			chart3->ChartAreas[0]->AxisY->IsStartedFromZero = false;




		}

	protected:
	
		~mainform()
		{
			if (components) delete components;
		
			if (mySerial != nullptr) {
				delete mySerial;
			}
		}
	
	protected:
		private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBoxBaud;
	private: System::Windows::Forms::TextBox^ textBoxPort;


	private: System::Windows::Forms::Button^ buttonConnect;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Label^ lblTemp1;
	private: System::Windows::Forms::Label^ lblCisnienie;
	private: System::Windows::Forms::Label^ lblTemp2;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart2;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart3;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::ComponentModel::IContainer^ components;


	private:



#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBoxBaud = (gcnew System::Windows::Forms::TextBox());
			this->textBoxPort = (gcnew System::Windows::Forms::TextBox());
			this->buttonConnect = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->lblTemp1 = (gcnew System::Windows::Forms::Label());
			this->lblCisnienie = (gcnew System::Windows::Forms::Label());
			this->lblTemp2 = (gcnew System::Windows::Forms::Label());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chart3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart3))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(145, 33);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(101, 16);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Enter buad rate:";
			this->label1->Click += gcnew System::EventHandler(this, &mainform::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(269, 33);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(67, 16);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Enter port:";
			// 
			// textBoxBaud
			// 
			this->textBoxBaud->Location = System::Drawing::Point(148, 52);
			this->textBoxBaud->Name = L"textBoxBaud";
			this->textBoxBaud->Size = System::Drawing::Size(100, 22);
			this->textBoxBaud->TabIndex = 2;
			// 
			// textBoxPort
			// 
			this->textBoxPort->Location = System::Drawing::Point(272, 52);
			this->textBoxPort->Name = L"textBoxPort";
			this->textBoxPort->Size = System::Drawing::Size(100, 22);
			this->textBoxPort->TabIndex = 3;
			this->textBoxPort->TextChanged += gcnew System::EventHandler(this, &mainform::textBox2_TextChanged);
			// 
			// buttonConnect
			// 
			this->buttonConnect->Location = System::Drawing::Point(272, 106);
			this->buttonConnect->Name = L"buttonConnect";
			this->buttonConnect->Size = System::Drawing::Size(75, 23);
			this->buttonConnect->TabIndex = 4;
			this->buttonConnect->Text = L"Connect";
			this->buttonConnect->UseVisualStyleBackColor = true;
			this->buttonConnect->Click += gcnew System::EventHandler(this, &mainform::button1_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(378, 39);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(139, 180);
			this->richTextBox1->TabIndex = 5;
			this->richTextBox1->Text = L"";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &mainform::timer1_Tick);
			// 
			// lblTemp1
			// 
			this->lblTemp1->AutoSize = true;
			this->lblTemp1->Location = System::Drawing::Point(148, 143);
			this->lblTemp1->Name = L"lblTemp1";
			this->lblTemp1->Size = System::Drawing::Size(0, 16);
			this->lblTemp1->TabIndex = 6;
			// 
			// lblCisnienie
			// 
			this->lblCisnienie->AutoSize = true;
			this->lblCisnienie->Location = System::Drawing::Point(148, 173);
			this->lblCisnienie->Name = L"lblCisnienie";
			this->lblCisnienie->Size = System::Drawing::Size(0, 16);
			this->lblCisnienie->TabIndex = 7;
			// 
			// lblTemp2
			// 
			this->lblTemp2->AutoSize = true;
			this->lblTemp2->Location = System::Drawing::Point(148, 203);
			this->lblTemp2->Name = L"lblTemp2";
			this->lblTemp2->Size = System::Drawing::Size(0, 16);
			this->lblTemp2->TabIndex = 8;
			// 
			// chart1
			// 
			this->chart1->BackColor = System::Drawing::Color::Transparent;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(12, 355);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Temp Bosch";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(684, 336);
			this->chart1->TabIndex = 9;
			this->chart1->Text = L"chart1";
			// 
			// chart2
			// 
			this->chart2->BackColor = System::Drawing::Color::Transparent;
			chartArea2->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea2);
			legend2->Name = L"Legend1";
			this->chart2->Legends->Add(legend2);
			this->chart2->Location = System::Drawing::Point(702, -12);
			this->chart2->Name = L"chart2";
			series2->ChartArea = L"ChartArea1";
			series2->Legend = L"Legend1";
			series2->Name = L"Pressure";
			this->chart2->Series->Add(series2);
			this->chart2->Size = System::Drawing::Size(693, 373);
			this->chart2->TabIndex = 10;
			this->chart2->Text = L"chart2";
			title1->Name = L"BMP280 Temp";
			this->chart2->Titles->Add(title1);
			// 
			// chart3
			// 
			this->chart3->BackColor = System::Drawing::Color::Transparent;
			this->chart3->BorderlineColor = System::Drawing::Color::Violet;
			chartArea3->Name = L"ChartArea1";
			this->chart3->ChartAreas->Add(chartArea3);
			legend3->Name = L"Legend1";
			this->chart3->Legends->Add(legend3);
			this->chart3->Location = System::Drawing::Point(717, 355);
			this->chart3->Name = L"chart3";
			series3->BackImageTransparentColor = System::Drawing::Color::Transparent;
			series3->ChartArea = L"ChartArea1";
			series3->Legend = L"Legend1";
			series3->Name = L"Temp DS18B20";
			this->chart3->Series->Add(series3);
			this->chart3->Size = System::Drawing::Size(729, 336);
			this->chart3->TabIndex = 11;
			this->chart3->Text = L"chart3";
			this->chart3->Click += gcnew System::EventHandler(this, &mainform::chart3_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(55, 143);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(87, 16);
			this->label3->TabIndex = 12;
			this->label3->Text = L"Temp Bosch:";
			this->label3->Click += gcnew System::EventHandler(this, &mainform::label3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(78, 173);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(64, 16);
			this->label4->TabIndex = 13;
			this->label4->Text = L"Pressure:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(37, 203);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(105, 16);
			this->label5->TabIndex = 14;
			this->label5->Text = L"Temp DS18B20:";
			// 
			// mainform
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(1423, 703);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->chart3);
			this->Controls->Add(this->chart2);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->lblTemp2);
			this->Controls->Add(this->lblCisnienie);
			this->Controls->Add(this->lblTemp1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->buttonConnect);
			this->Controls->Add(this->textBoxPort);
			this->Controls->Add(this->textBoxBaud);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"mainform";
			this->Text = L"Weather Station";
			this->Load += gcnew System::EventHandler(this, &mainform::mainform_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void mainform_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		if (mySerial != nullptr) {
			timer1->Stop(); 
			delete mySerial;
			mySerial = nullptr;
			buttonConnect->Text = "Po³¹cz";
			buttonConnect->BackColor = SystemColors::Control;
			richTextBox1->AppendText("--- Roz³¹czono ---\n");
			return;
		}

		
		std::string port = marshal_as<std::string>(textBoxPort->Text); // np. "COM5"
		unsigned long baud;

		try {
			baud = System::Convert::ToUInt32(textBoxBaud->Text); // np. 115200
		}
		catch (...) {
			MessageBox::Show("B³êdna prêdkoœæ (Baud Rate)!");
			return;
		}

		richTextBox1->AppendText("Próbujê po³¹czyæ z: " + textBoxPort->Text + "...\n");

		try {
			
			mySerial = new serial::Serial(port, baud, serial::Timeout::simpleTimeout(1000));

			if (mySerial->isOpen()) {
				richTextBox1->AppendText("SUKCES: Port otwarty. Nas³uchiwanie...\n");
				buttonConnect->Text = "Roz³¹cz";
				buttonConnect->BackColor = Color::LightGreen;

		
				timer1->Start();
			}
		}
		catch (std::exception& e) {
			MessageBox::Show("B£¥D KRYTYCZNY: Nie mo¿na otworzyæ portu!\nSprawdŸ czy " + textBoxPort->Text + " istnieje.");
			mySerial = nullptr;
		}
	}
private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

	if (mySerial != nullptr && mySerial->isOpen()) {
		try {
			while (mySerial->available()) {

				std::string rawLine = mySerial->readline();
				String^ linia = msclr::interop::marshal_as<String^>(rawLine);
				linia = linia->Trim();

				if (linia->Length == 0) continue;


				String^ liniaDoParsowania = linia;

			
				liniaDoParsowania = liniaDoParsowania->Replace("DS18B20", "");
				liniaDoParsowania = liniaDoParsowania->Replace("Bosch", "");
				liniaDoParsowania = liniaDoParsowania->Replace("Temp", "");
				liniaDoParsowania = liniaDoParsowania->Replace("Press", "");

		
				Regex^ wzor = gcnew Regex("-?[0-9]+[\\.,]?[0-9]*");
				Match^ dopasowanie = wzor->Match(liniaDoParsowania);

				double wartosc = 0;
				bool czyUdaloSiePobracLiczbe = false;

				if (dopasowanie->Success) {
					String^ separator = System::Globalization::NumberFormatInfo::CurrentInfo->NumberDecimalSeparator;
					String^ czystaLiczba = dopasowanie->Value->Replace(".", separator)->Replace(",", separator);

					try {
						wartosc = Convert::ToDouble(czystaLiczba);
						czyUdaloSiePobracLiczbe = true;
					}
					catch (...) { czyUdaloSiePobracLiczbe = false; }
				}

				if (!czyUdaloSiePobracLiczbe) continue;

			
				// === TEMP 1 (BOSCH) ===
				if (linia->Contains("Bosch")) {
					lblTemp1->Text = wartosc.ToString("F2") + " C";
					chart1->Series[0]->Points->AddY(wartosc);
					if (chart1->Series[0]->Points->Count > 40) chart1->Series[0]->Points->RemoveAt(0);
					chart1->ChartAreas[0]->RecalculateAxesScale();
				}

				// === CISNIENIE ===
				else if (linia->Contains("Press")) {
					lblCisnienie->Text = wartosc.ToString("F2") + " Pa";
					chart2->Series[0]->Points->AddY(wartosc);
					if (chart2->Series[0]->Points->Count > 40) chart2->Series[0]->Points->RemoveAt(0);
					chart2->ChartAreas[0]->RecalculateAxesScale();
				}

				// === TEMP 2 (DS18B20) ===
				else if (linia->Contains("DS18B20")) {
					lblTemp2->Text = wartosc.ToString("F2") + " C";
					chart3->Series[0]->Points->AddY(wartosc);
					if (chart3->Series[0]->Points->Count > 40) chart3->Series[0]->Points->RemoveAt(0);
					chart3->ChartAreas[0]->RecalculateAxesScale();
				}
			}
		}
		catch (std::exception& e) {}
	}
}
private: System::Void chart3_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void chart2_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
