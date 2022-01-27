#pragma once
#include "OMSIPresentationTools.h"


/* Copyright 2022 sjain882
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     https://www.gnu.org/licenses/gpl-3.0.en.html
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


namespace OMSIPresToolsCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	System::Decimal oldFovValue = (System::Decimal)45.0;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}


	private: System::Windows::Forms::TrackBar^ f4FovTrackbar;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ f4FovMaxLabel;

	private: System::Windows::Forms::LinkLabel^ labelAboutVersionGithub;



	private: System::Windows::Forms::LinkLabel^ labelYouTube;
	private: System::Windows::Forms::PictureBox^ pictureYouTubeIcon;
	private: System::Windows::Forms::PictureBox^ pictureSteamIcon;

	private: System::Windows::Forms::LinkLabel^ labelSteamGuide;


	private: System::Windows::Forms::Label^ f4FovStatusLabel;
	private: System::Windows::Forms::CheckBox^ f4FovToggle;
	private: System::Windows::Forms::NumericUpDown^ f4FovNumericUpDown;
	private: System::Windows::Forms::Label^ f4FovTitle;
	private: System::Windows::Forms::Label^ f4FovMinLabel;
	private: System::Windows::Forms::Label^ f4FovRawLabel;
	private: System::Windows::Forms::Label^ f4fovvaluetmp2;
	private: System::Windows::Forms::CheckBox^ pinToTopToggle;
	private: System::Windows::Forms::LinkLabel^ labelAboutThanksTo;
	private: System::Windows::Forms::PictureBox^ logoPicture;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->f4FovTrackbar = (gcnew System::Windows::Forms::TrackBar());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->f4FovMaxLabel = (gcnew System::Windows::Forms::Label());
			this->labelAboutVersionGithub = (gcnew System::Windows::Forms::LinkLabel());
			this->labelYouTube = (gcnew System::Windows::Forms::LinkLabel());
			this->pictureYouTubeIcon = (gcnew System::Windows::Forms::PictureBox());
			this->pictureSteamIcon = (gcnew System::Windows::Forms::PictureBox());
			this->labelSteamGuide = (gcnew System::Windows::Forms::LinkLabel());
			this->f4FovStatusLabel = (gcnew System::Windows::Forms::Label());
			this->f4FovToggle = (gcnew System::Windows::Forms::CheckBox());
			this->f4FovNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->f4FovTitle = (gcnew System::Windows::Forms::Label());
			this->f4FovMinLabel = (gcnew System::Windows::Forms::Label());
			this->f4FovRawLabel = (gcnew System::Windows::Forms::Label());
			this->f4fovvaluetmp2 = (gcnew System::Windows::Forms::Label());
			this->pinToTopToggle = (gcnew System::Windows::Forms::CheckBox());
			this->labelAboutThanksTo = (gcnew System::Windows::Forms::LinkLabel());
			this->logoPicture = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4FovTrackbar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureYouTubeIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureSteamIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4FovNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->logoPicture))->BeginInit();
			this->SuspendLayout();
			// 
			// f4FovTrackbar
			// 
			this->f4FovTrackbar->AutoSize = false;
			this->f4FovTrackbar->Enabled = false;
			this->f4FovTrackbar->Location = System::Drawing::Point(23, 127);
			this->f4FovTrackbar->Maximum = 1500;
			this->f4FovTrackbar->Minimum = 10;
			this->f4FovTrackbar->Name = L"f4FovTrackbar";
			this->f4FovTrackbar->Size = System::Drawing::Size(385, 45);
			this->f4FovTrackbar->TabIndex = 3;
			this->f4FovTrackbar->TickFrequency = 1500;
			this->f4FovTrackbar->Value = 450;
			this->f4FovTrackbar->Scroll += gcnew System::EventHandler(this, &MyForm::f4FovTrackbar_Scroll);
			// 
			// label4
			// 
			this->label4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label4->Location = System::Drawing::Point(16, 201);
			this->label4->MaximumSize = System::Drawing::Size(0, 2);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 2);
			this->label4->TabIndex = 9;
			// 
			// f4FovMaxLabel
			// 
			this->f4FovMaxLabel->AutoSize = true;
			this->f4FovMaxLabel->Location = System::Drawing::Point(379, 159);
			this->f4FovMaxLabel->Name = L"f4FovMaxLabel";
			this->f4FovMaxLabel->Size = System::Drawing::Size(34, 13);
			this->f4FovMaxLabel->TabIndex = 11;
			this->f4FovMaxLabel->Text = L"150.0";
			// 
			// labelAboutVersionGithub
			// 
			this->labelAboutVersionGithub->AutoSize = true;
			this->labelAboutVersionGithub->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			this->labelAboutVersionGithub->LinkArea = System::Windows::Forms::LinkArea(15, 6);
			this->labelAboutVersionGithub->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->labelAboutVersionGithub->Location = System::Drawing::Point(162, 299);
			this->labelAboutVersionGithub->Name = L"labelAboutVersionGithub";
			this->labelAboutVersionGithub->Size = System::Drawing::Size(119, 19);
			this->labelAboutVersionGithub->TabIndex = 6;
			this->labelAboutVersionGithub->TabStop = true;
			this->labelAboutVersionGithub->Text = L"v0.1.0 alpha • Github";
			this->labelAboutVersionGithub->UseCompatibleTextRendering = true;
			this->labelAboutVersionGithub->VisitedLinkColor = System::Drawing::Color::Blue;
			this->labelAboutVersionGithub->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::labelAboutVersionGithub_LinkClicked);
			// 
			// labelYouTube
			// 
			this->labelYouTube->AutoSize = true;
			this->labelYouTube->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelYouTube->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->labelYouTube->Location = System::Drawing::Point(70, 215);
			this->labelYouTube->Name = L"labelYouTube";
			this->labelYouTube->Size = System::Drawing::Size(204, 15);
			this->labelYouTube->TabIndex = 4;
			this->labelYouTube->TabStop = true;
			this->labelYouTube->Text = L"YouTube tutorial && suggested usage";
			this->labelYouTube->VisitedLinkColor = System::Drawing::Color::Blue;
			this->labelYouTube->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::labelYouTube_LinkClicked);
			// 
			// pictureYouTubeIcon
			// 
			this->pictureYouTubeIcon->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureYouTubeIcon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureYouTubeIcon.Image")));
			this->pictureYouTubeIcon->Location = System::Drawing::Point(45, 212);
			this->pictureYouTubeIcon->Name = L"pictureYouTubeIcon";
			this->pictureYouTubeIcon->Size = System::Drawing::Size(24, 23);
			this->pictureYouTubeIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureYouTubeIcon->TabIndex = 23;
			this->pictureYouTubeIcon->TabStop = false;
			this->pictureYouTubeIcon->Click += gcnew System::EventHandler(this, &MyForm::pictureYouTubeIcon_Click);
			// 
			// pictureSteamIcon
			// 
			this->pictureSteamIcon->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureSteamIcon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureSteamIcon.Image")));
			this->pictureSteamIcon->Location = System::Drawing::Point(285, 210);
			this->pictureSteamIcon->Name = L"pictureSteamIcon";
			this->pictureSteamIcon->Size = System::Drawing::Size(20, 27);
			this->pictureSteamIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureSteamIcon->TabIndex = 25;
			this->pictureSteamIcon->TabStop = false;
			this->pictureSteamIcon->Click += gcnew System::EventHandler(this, &MyForm::pictureGitHubIcon_Click);
			// 
			// labelSteamGuide
			// 
			this->labelSteamGuide->AutoSize = true;
			this->labelSteamGuide->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelSteamGuide->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->labelSteamGuide->Location = System::Drawing::Point(307, 215);
			this->labelSteamGuide->Name = L"labelSteamGuide";
			this->labelSteamGuide->Size = System::Drawing::Size(77, 15);
			this->labelSteamGuide->TabIndex = 5;
			this->labelSteamGuide->TabStop = true;
			this->labelSteamGuide->Text = L"Steam guide";
			this->labelSteamGuide->VisitedLinkColor = System::Drawing::Color::Blue;
			this->labelSteamGuide->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::labelSteamGuide_LinkClicked);
			// 
			// f4FovStatusLabel
			// 
			this->f4FovStatusLabel->AutoSize = true;
			this->f4FovStatusLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->f4FovStatusLabel->Location = System::Drawing::Point(73, 244);
			this->f4FovStatusLabel->Name = L"f4FovStatusLabel";
			this->f4FovStatusLabel->Size = System::Drawing::Size(276, 15);
			this->f4FovStatusLabel->TabIndex = 29;
			this->f4FovStatusLabel->Text = L"Controls will be unavailable until a map is loaded.";
			// 
			// f4FovToggle
			// 
			this->f4FovToggle->AutoSize = true;
			this->f4FovToggle->Location = System::Drawing::Point(108, 72);
			this->f4FovToggle->Name = L"f4FovToggle";
			this->f4FovToggle->Size = System::Drawing::Size(65, 17);
			this->f4FovToggle->TabIndex = 1;
			this->f4FovToggle->Text = L"Enabled";
			this->f4FovToggle->UseVisualStyleBackColor = true;
			this->f4FovToggle->CheckedChanged += gcnew System::EventHandler(this, &MyForm::f4FovToggle_CheckedChanged);
			// 
			// f4FovNumericUpDown
			// 
			this->f4FovNumericUpDown->DecimalPlaces = 1;
			this->f4FovNumericUpDown->Enabled = false;
			this->f4FovNumericUpDown->Location = System::Drawing::Point(256, 70);
			this->f4FovNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 150, 0, 0, 0 });
			this->f4FovNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9, 0, 0, 65536 });
			this->f4FovNumericUpDown->Name = L"f4FovNumericUpDown";
			this->f4FovNumericUpDown->Size = System::Drawing::Size(60, 20);
			this->f4FovNumericUpDown->TabIndex = 2;
			this->f4FovNumericUpDown->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->f4FovNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 45, 0, 0, 0 });
			this->f4FovNumericUpDown->ValueChanged += gcnew System::EventHandler(this, &MyForm::f4FovNumericUpDown_ValueChanged);
			// 
			// f4FovTitle
			// 
			this->f4FovTitle->AutoSize = true;
			this->f4FovTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->f4FovTitle->Location = System::Drawing::Point(105, 22);
			this->f4FovTitle->Name = L"f4FovTitle";
			this->f4FovTitle->Size = System::Drawing::Size(211, 15);
			this->f4FovTitle->TabIndex = 7;
			this->f4FovTitle->Text = L"Free Map (F4) Camera FOV Value (°):";
			// 
			// f4FovMinLabel
			// 
			this->f4FovMinLabel->AutoSize = true;
			this->f4FovMinLabel->Location = System::Drawing::Point(26, 159);
			this->f4FovMinLabel->Name = L"f4FovMinLabel";
			this->f4FovMinLabel->Size = System::Drawing::Size(22, 13);
			this->f4FovMinLabel->TabIndex = 10;
			this->f4FovMinLabel->Text = L"1.0";
			// 
			// f4FovRawLabel
			// 
			this->f4FovRawLabel->AutoSize = true;
			this->f4FovRawLabel->Location = System::Drawing::Point(218, 73);
			this->f4FovRawLabel->Name = L"f4FovRawLabel";
			this->f4FovRawLabel->Size = System::Drawing::Size(32, 13);
			this->f4FovRawLabel->TabIndex = 20;
			this->f4FovRawLabel->Text = L"Raw:";
			// 
			// f4fovvaluetmp2
			// 
			this->f4fovvaluetmp2->AutoSize = true;
			this->f4fovvaluetmp2->Location = System::Drawing::Point(333, 74);
			this->f4fovvaluetmp2->Name = L"f4fovvaluetmp2";
			this->f4fovvaluetmp2->Size = System::Drawing::Size(0, 13);
			this->f4fovvaluetmp2->TabIndex = 28;
			// 
			// pinToTopToggle
			// 
			this->pinToTopToggle->Appearance = System::Windows::Forms::Appearance::Button;
			this->pinToTopToggle->AutoSize = true;
			this->pinToTopToggle->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pinToTopToggle.Image")));
			this->pinToTopToggle->Location = System::Drawing::Point(12, 12);
			this->pinToTopToggle->Name = L"pinToTopToggle";
			this->pinToTopToggle->Size = System::Drawing::Size(30, 30);
			this->pinToTopToggle->TabIndex = 0;
			this->pinToTopToggle->UseVisualStyleBackColor = true;
			this->pinToTopToggle->CheckedChanged += gcnew System::EventHandler(this, &MyForm::pinToTopToggle_CheckedChanged);
			// 
			// labelAboutThanksTo
			// 
			this->labelAboutThanksTo->AutoSize = true;
			this->labelAboutThanksTo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			this->labelAboutThanksTo->LinkArea = System::Windows::Forms::LinkArea(18, 12);
			this->labelAboutThanksTo->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->labelAboutThanksTo->Location = System::Drawing::Point(162, 319);
			this->labelAboutThanksTo->Name = L"labelAboutThanksTo";
			this->labelAboutThanksTo->Size = System::Drawing::Size(161, 19);
			this->labelAboutThanksTo->TabIndex = 8;
			this->labelAboutThanksTo->TabStop = true;
			this->labelAboutThanksTo->Text = L"Created by sjain (full credits)";
			this->labelAboutThanksTo->UseCompatibleTextRendering = true;
			this->labelAboutThanksTo->VisitedLinkColor = System::Drawing::Color::Blue;
			this->labelAboutThanksTo->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::labelAboutThanksTo_LinkClicked);
			// 
			// logoPicture
			// 
			this->logoPicture->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"logoPicture.Image")));
			this->logoPicture->Location = System::Drawing::Point(100, 291);
			this->logoPicture->Name = L"logoPicture";
			this->logoPicture->Size = System::Drawing::Size(52, 48);
			this->logoPicture->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->logoPicture->TabIndex = 30;
			this->logoPicture->TabStop = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(431, 371);
			this->Controls->Add(this->logoPicture);
			this->Controls->Add(this->pinToTopToggle);
			this->Controls->Add(this->f4FovStatusLabel);
			this->Controls->Add(this->f4fovvaluetmp2);
			this->Controls->Add(this->labelSteamGuide);
			this->Controls->Add(this->pictureSteamIcon);
			this->Controls->Add(this->pictureYouTubeIcon);
			this->Controls->Add(this->labelYouTube);
			this->Controls->Add(this->f4FovRawLabel);
			this->Controls->Add(this->labelAboutThanksTo);
			this->Controls->Add(this->labelAboutVersionGithub);
			this->Controls->Add(this->f4FovMaxLabel);
			this->Controls->Add(this->f4FovMinLabel);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->f4FovTitle);
			this->Controls->Add(this->f4FovNumericUpDown);
			this->Controls->Add(this->f4FovToggle);
			this->Controls->Add(this->f4FovTrackbar);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->Text = L"OMSI Presentation Tools";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4FovTrackbar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureYouTubeIcon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureSteamIcon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4FovNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->logoPicture))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void labelAboutThanksTo2_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {

		System::Diagnostics::Process::Start("https://github.com/win32kbase");

	}

	private: System::Void labelAboutThanksTo_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {

		System::Diagnostics::Process::Start("https://github.com/sjain882/OMSI-Presentation-Tools/blob/main/.github/README.md#credits");

	}

	private: System::Void labelAboutAuthor_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {

		System::Diagnostics::Process::Start("https://github.com/sjain882");

	}

	private: System::Void labelAboutVersionGithub_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {

		System::Diagnostics::Process::Start("https://github.com/sjain882/OMSI-Presentation-Tools");

	}

	private: System::Void labelSteamGuide_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {

		System::Diagnostics::Process::Start("https://steamcommunity.com/sharedfiles/filedetails/?id=2722795667");

	}

	private: System::Void pictureGitHubIcon_Click(System::Object^ sender, System::EventArgs^ e) {

		System::Diagnostics::Process::Start("https://steamcommunity.com/sharedfiles/filedetails/?id=2722795667");

	}

	private: System::Void labelYouTube_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {

		System::Diagnostics::Process::Start("https://www.youtube.com/watch?v=YrbM-jaZYls");

	}


	private: System::Void pictureYouTubeIcon_Click(System::Object^ sender, System::EventArgs^ e) {

		System::Diagnostics::Process::Start("https://www.youtube.com/watch?v=YrbM-jaZYls");

	}


	// F4 FoV Checkbox toggle
	private: System::Void f4FovToggle_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

		// Only continue if a map is currently loaded, otherwise disable the controls again.
		if (isMapCurrentlyLoaded) {

			// Communicate this change to dllmain.cpp
			ToggleF4FovApplication();

			// Invert all relevant enabled status booleans
			this->f4FovTrackbar->Enabled = !this->f4FovTrackbar->Enabled;
			this->f4FovNumericUpDown->Enabled = !this->f4FovNumericUpDown->Enabled;

			// If everything is disabled...
			if ((this->f4FovTrackbar->Enabled == false) && (this->f4FovNumericUpDown->Enabled == false)) {

				// Just disabled FOV application
				justEnabledFOVApplication = false;

				// Set UI values to 45.0 degrees FoV
				this->f4FovTrackbar->Value = 450;
				this->f4FovNumericUpDown->Value = (System::Decimal)45.0;

				// Retain the previous FoV value before disabling
				f4FovHoldValue = f4FovActValue;

				// Set the actual F4 FoV back to 45
				f4FovActValue = 45.0;

			} else {

				// Just enabled FOV application
				justEnabledFOVApplication = true;

				// Restore the UI values to the previous value
				this->f4FovTrackbar->Value = (int)f4FovHoldValue * 10.0;
				this->f4FovNumericUpDown->Value = (System::Decimal)f4FovHoldValue;

				// Set the actual FoV back to the previous value
				f4FovActValue = f4FovHoldValue;

			}

		} else {
			this->f4FovToggle->Checked = false;
			this->f4FovTrackbar->Enabled = false;
			this->f4FovNumericUpDown->Enabled = false;
			DisableF4FovApplication();
		}

	}
	


	/* F4 FoV trackbar (slider) scroll event.
	*  Trackbar don't support decimal values so throughout the form we will be using the FoV * 10 */
	private: System::Void f4FovTrackbar_Scroll(System::Object^ sender, System::EventArgs^ e) {

		// The user just scrolled
		justScrolled = true;

		/* Set the actual FoV to the new value, casting to a float 
		* and dividing by 10.0 float to prevent precision issues */
		f4FovActValue = (float)this->f4FovTrackbar->Value / 10.0;

		// Cast to managed decimal value and set to the Numeric Up Down box too
		this->f4FovNumericUpDown->Value = (System::Decimal)this->f4FovTrackbar->Value / (System::Decimal)10.0;

		// Scroll event ended
		justScrolled = false;
	}



	// Numeric Up Down box change event
	private: System::Void f4FovNumericUpDown_ValueChanged(System::Object^ sender, System::EventArgs^ e) {

		// If the user just enabled the FoV checkbox...
		if (justEnabledFOVApplication) {
			
			//... and hasn't just scrolled the trackbar
			if (!justScrolled) {

				// Copy the new FoV to a new variable
				System::Decimal newFovValue = f4FovNumericUpDown->Value;

				// If the user pressed the up button or increased the FoV
				if (oldFovValue < newFovValue) {

					// Set the actual FoV value to this new value
					f4FovActValue = (float)this->f4FovNumericUpDown->Value;

					// Set the trackbar value to this value
					this->f4FovTrackbar->Value = (int)this->f4FovNumericUpDown->Value * 10.0;

				// If the user pressed the down button or decreased the FoV
				} else if (oldFovValue > newFovValue) {

					// If it's 2.1, manually floor it to 1.0 to avoid exception due to behaviour of WinForms
					if (newFovValue < (System::Decimal(2.1))) {

						// Set the actual F4 FoV to 1
						f4FovActValue = (float)1.0;

						// Set the NumericUpDown value to 1.0
						this->f4FovNumericUpDown->Value = (System::Decimal)1.0;

						// Set the trackbar to the minimum (10)
						this->f4FovTrackbar->Value = 10;

					// If its just a normal decrease..
					} else {

						// Set the actual fov to the new value
						f4FovActValue = (float)this->f4FovNumericUpDown->Value;

						// Set the trackbar to the new value
						this->f4FovTrackbar->Value = (int)this->f4FovNumericUpDown->Value * 10.0;
					}
				}

				// Update the old FoV tracker
				oldFovValue = newFovValue;
			}
		}
	}
	


	// When the user is closing the form
	private: System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {

		// Prompt them and if they confirm (click Yes):
		if (MessageBox::Show("Are you sure you want to quit?\n\n"
							 "OMSI 2 will remain running and the F4 FOV will be reset to default.\n\n"
							 "You will not be able to relaunch OPT until you next launch OMSI.",
							 "OMSI Presentation Tools", MessageBoxButtons::YesNo,
							 MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {


			// Set the actual FoV back to the default (45.0)
			f4FovActValue = (float)45.0;

			// Stop the main program loop
			isProcessActive = false;

		// If they cancel (click No)
		} else {
			e->Cancel = true;	// Cancel the close event
		}
	}



	// Always on top toggle button
	private: System::Void pinToTopToggle_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		TopMost = !TopMost;
	}

};
}
