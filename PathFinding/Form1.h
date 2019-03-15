#pragma once;

namespace PathFinding {

	using namespace System;
    using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
    
    Grid Map;//Declars an instants of the Grid class
    int PathFindingType;//Used to identify what algarithem is going to be used, 
                        //Best First = 0, Dijkstra's = 1, A* = 2.

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::PictureBox^  pictureBox1;
    private: System::Windows::Forms::GroupBox^  groupBox1;
    private: System::Windows::Forms::Button^  button3;
    private: System::Windows::Forms::Button^  button2;
    private: System::Windows::Forms::Button^  button1;
    private: System::Windows::Forms::GroupBox^  groupBox2;
    private: System::Windows::Forms::Button^  button4;

    private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
    private: System::Windows::Forms::Button^  button5;

    private: System::Windows::Forms::GroupBox^  groupBox3;
    private: System::Windows::Forms::Button^  button7;
    private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
    private: System::Windows::Forms::GroupBox^  groupBox4;
    private: System::Windows::Forms::Button^  button9;
    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::RichTextBox^  richTextBox1;
    private: System::Windows::Forms::GroupBox^  groupBox5;
    private: System::Windows::Forms::Label^  label3;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::Label^  label4;
    private: System::Windows::Forms::Label^  label5;
    private: System::Windows::Forms::Label^  label7;
    private: System::Windows::Forms::Label^  label6;
    private: System::Windows::Forms::Label^  label8;

    protected:
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
            this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
            this->button3 = (gcnew System::Windows::Forms::Button());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
            this->button4 = (gcnew System::Windows::Forms::Button());
            this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
            this->button5 = (gcnew System::Windows::Forms::Button());
            this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
            this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
            this->button7 = (gcnew System::Windows::Forms::Button());
            this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
            this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
            this->button9 = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
            this->groupBox1->SuspendLayout();
            this->groupBox2->SuspendLayout();
            this->groupBox3->SuspendLayout();
            this->groupBox4->SuspendLayout();
            this->groupBox5->SuspendLayout();
            this->SuspendLayout();
            // 
            // pictureBox1
            // 
            this->pictureBox1->BackColor = System::Drawing::Color::White;
            this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->pictureBox1->Location = System::Drawing::Point(12, 35);
            this->pictureBox1->Name = L"pictureBox1";
            this->pictureBox1->Size = System::Drawing::Size(600, 600);
            this->pictureBox1->TabIndex = 0;
            this->pictureBox1->TabStop = false;
            // 
            // groupBox1
            // 
            this->groupBox1->Controls->Add(this->button3);
            this->groupBox1->Controls->Add(this->button2);
            this->groupBox1->Controls->Add(this->button1);
            this->groupBox1->Location = System::Drawing::Point(618, 35);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Size = System::Drawing::Size(153, 135);
            this->groupBox1->TabIndex = 1;
            this->groupBox1->TabStop = false;
            this->groupBox1->Text = L"1. Algorithms";
            // 
            // button3
            // 
            this->button3->Location = System::Drawing::Point(6, 97);
            this->button3->Name = L"button3";
            this->button3->Size = System::Drawing::Size(141, 33);
            this->button3->TabIndex = 1;
            this->button3->Text = L"A*";
            this->button3->UseVisualStyleBackColor = true;
            this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(6, 58);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(141, 33);
            this->button2->TabIndex = 2;
            this->button2->Text = L"Dijkstra\'s";
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(6, 19);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(141, 33);
            this->button1->TabIndex = 1;
            this->button1->Text = L"Best-first ";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
            // 
            // groupBox2
            // 
            this->groupBox2->Controls->Add(this->button4);
            this->groupBox2->Enabled = false;
            this->groupBox2->Location = System::Drawing::Point(777, 35);
            this->groupBox2->Name = L"groupBox2";
            this->groupBox2->Size = System::Drawing::Size(153, 63);
            this->groupBox2->TabIndex = 2;
            this->groupBox2->TabStop = false;
            this->groupBox2->Text = L"2. Load Map";
            // 
            // button4
            // 
            this->button4->Location = System::Drawing::Point(6, 19);
            this->button4->Name = L"button4";
            this->button4->Size = System::Drawing::Size(141, 33);
            this->button4->TabIndex = 0;
            this->button4->Text = L"Load Map";
            this->button4->UseVisualStyleBackColor = true;
            this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
            // 
            // openFileDialog1
            // 
            this->openFileDialog1->FileName = L"openFileDialog1";
            // 
            // button5
            // 
            this->button5->Location = System::Drawing::Point(618, 602);
            this->button5->Name = L"button5";
            this->button5->Size = System::Drawing::Size(153, 33);
            this->button5->TabIndex = 0;
            this->button5->Text = L"Clear Map";
            this->button5->UseVisualStyleBackColor = true;
            this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
            // 
            // groupBox3
            // 
            this->groupBox3->Controls->Add(this->richTextBox1);
            this->groupBox3->Controls->Add(this->button7);
            this->groupBox3->Location = System::Drawing::Point(618, 176);
            this->groupBox3->Name = L"groupBox3";
            this->groupBox3->Size = System::Drawing::Size(312, 394);
            this->groupBox3->TabIndex = 5;
            this->groupBox3->TabStop = false;
            this->groupBox3->Text = L"Route Taken";
            // 
            // richTextBox1
            // 
            this->richTextBox1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->richTextBox1->Location = System::Drawing::Point(7, 21);
            this->richTextBox1->Name = L"richTextBox1";
            this->richTextBox1->ReadOnly = true;
            this->richTextBox1->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
            this->richTextBox1->Size = System::Drawing::Size(299, 328);
            this->richTextBox1->TabIndex = 2;
            this->richTextBox1->Text = L"";
            // 
            // button7
            // 
            this->button7->Location = System::Drawing::Point(7, 355);
            this->button7->Name = L"button7";
            this->button7->Size = System::Drawing::Size(141, 33);
            this->button7->TabIndex = 1;
            this->button7->Text = L"Save to Text File";
            this->button7->UseVisualStyleBackColor = true;
            this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
            // 
            // groupBox4
            // 
            this->groupBox4->Controls->Add(this->button9);
            this->groupBox4->Enabled = false;
            this->groupBox4->Location = System::Drawing::Point(777, 104);
            this->groupBox4->Name = L"groupBox4";
            this->groupBox4->Size = System::Drawing::Size(153, 62);
            this->groupBox4->TabIndex = 6;
            this->groupBox4->TabStop = false;
            this->groupBox4->Text = L"3. Start";
            // 
            // button9
            // 
            this->button9->Location = System::Drawing::Point(6, 19);
            this->button9->Name = L"button9";
            this->button9->Size = System::Drawing::Size(141, 33);
            this->button9->TabIndex = 1;
            this->button9->Text = L"Start Path Finding";
            this->button9->UseVisualStyleBackColor = true;
            this->button9->Click += gcnew System::EventHandler(this, &Form1::button9_Click);
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(17, 641);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(0, 13);
            this->label1->TabIndex = 7;
            // 
            // groupBox5
            // 
            this->groupBox5->Controls->Add(this->label8);
            this->groupBox5->Controls->Add(this->label7);
            this->groupBox5->Controls->Add(this->label6);
            this->groupBox5->Controls->Add(this->label5);
            this->groupBox5->Controls->Add(this->label4);
            this->groupBox5->Controls->Add(this->label3);
            this->groupBox5->Controls->Add(this->label2);
            this->groupBox5->Location = System::Drawing::Point(777, 576);
            this->groupBox5->Name = L"groupBox5";
            this->groupBox5->Size = System::Drawing::Size(147, 59);
            this->groupBox5->TabIndex = 8;
            this->groupBox5->TabStop = false;
            this->groupBox5->Text = L"Key";
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->BackColor = System::Drawing::Color::Red;
            this->label8->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->label8->Location = System::Drawing::Point(7, 42);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(112, 13);
            this->label8->TabIndex = 6;
            this->label8->Text = L"Path (Trasparent Red)";
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->BackColor = System::Drawing::Color::Yellow;
            this->label7->Location = System::Drawing::Point(41, 29);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(26, 13);
            this->label7->TabIndex = 5;
            this->label7->Text = L"End";
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->BackColor = System::Drawing::Color::LightSalmon;
            this->label6->Location = System::Drawing::Point(41, 16);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(29, 13);
            this->label6->TabIndex = 4;
            this->label6->Text = L"Start";
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->label5->Location = System::Drawing::Point(7, 29);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(31, 13);
            this->label5->TabIndex = 3;
            this->label5->Text = L"Clear";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->BackColor = System::Drawing::Color::Green;
            this->label4->ForeColor = System::Drawing::SystemColors::ControlLightLight;
            this->label4->Location = System::Drawing::Point(76, 29);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(36, 13);
            this->label4->TabIndex = 2;
            this->label4->Text = L"Wood";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->BackColor = System::Drawing::Color::Blue;
            this->label3->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->label3->Location = System::Drawing::Point(76, 16);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(36, 13);
            this->label3->TabIndex = 1;
            this->label3->Text = L"Water";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->BackColor = System::Drawing::SystemColors::ControlText;
            this->label2->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
            this->label2->Location = System::Drawing::Point(7, 16);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(28, 13);
            this->label2->TabIndex = 0;
            this->label2->Text = L"Wall";
            // 
            // Form1
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(937, 664);
            this->Controls->Add(this->groupBox5);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->groupBox4);
            this->Controls->Add(this->groupBox3);
            this->Controls->Add(this->button5);
            this->Controls->Add(this->groupBox2);
            this->Controls->Add(this->groupBox1);
            this->Controls->Add(this->pictureBox1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->Name = L"Form1";
            this->Text = L"Path Finding";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
            this->groupBox1->ResumeLayout(false);
            this->groupBox2->ResumeLayout(false);
            this->groupBox3->ResumeLayout(false);
            this->groupBox4->ResumeLayout(false);
            this->groupBox5->ResumeLayout(false);
            this->groupBox5->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    //***User Interface Controls***//
    private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
    {
        /***Button to choose Best-First***/
        PathFindingType = 0;
        groupBox1->Enabled = false;
        groupBox2->Enabled = true;
    }

    private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
    {
        /***Button to choose Dijkstra's***/
        PathFindingType = 1;
        groupBox1->Enabled = false;
        groupBox2->Enabled = true;
    }
    private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
    {
        /***Button to choose A* ***/
        PathFindingType = 2;
        groupBox1->Enabled = false;
        groupBox2->Enabled = true;
    }


    private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) 
    {
        
        //This Button opens two open file dilogs, one to get the map file and the other to get the file
        //with the coordanates in. They will surgest the default name based on what algrathem is being 
        //used so the user can just press open. All the data is stored in a instants of the Grid class
        //then then a image is generated from that data and output using a picture box.
        openFileDialog1->Title = "Open A Map File";
        openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
        if ( PathFindingType == 0 || PathFindingType == 2 ) { openFileDialog1->FileName = "m1.txt"; }
        else if ( PathFindingType == 1 ) { openFileDialog1->FileName = "d1.txt"; }
        String^ line;
        if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
        {
                try
                {
                    StreamReader^ sr = gcnew StreamReader( openFileDialog1->OpenFile() );
                    try
                    {
                        
                        int j = 9;
                        while ( line = sr->ReadLine() )
                        {
                                for ( int i = 9; i > -1; i-- )
                                {
                                    Map.AddMapData( line[i], i, j );
                                }
                            j--;
                        }
                    }
                    finally
                    {
                        if ( sr )
                            delete (IDisposable^)sr;
                    }
                }
                catch ( Exception^ e ) 
                {
                    richTextBox1->Text = e->Message;
                }


        }
 
        line = "";
        openFileDialog1->Title = "Open A Cords File";
        openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
        if ( PathFindingType == 0 || PathFindingType == 2 ) { openFileDialog1->FileName = "coords.txt"; }
        else if ( PathFindingType == 1 ) { openFileDialog1->FileName = "dcoords.txt"; }

        if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
        {
                int i = 0;
                try
                {
                    StreamReader^ sr = gcnew StreamReader( openFileDialog1->OpenFile() );
                    try
                    {
                        while ( line = sr->ReadLine())
                        {
                            if ( i == 0){ Map.AddStartCordz( line[0], line[2] ); }
                            if ( i == 1){ Map.AddEndCordz( line[0], line[2] ); }
                            i++;                                            
                        }
                    }
                    finally
                    {
                        if ( sr )
                            delete (IDisposable^)sr;
                    }
                }
                catch ( Exception^ e ) 
                {
                    richTextBox1->Text = e->Message;
                }

                groupBox2->Enabled = false;
                groupBox4->Enabled = true;
                pictureBox1->Image = Map.CreateGrid();
        }


    }
    private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) 
    {
        //Sends a refrance of Map and of the rich text box on form1 to the right algraithem
        //based on what one was chosen, the algraithems read and write to the map class and
        //show details of what happened in the rich text box. If the algrithem returns true 
        //then the map image is updated else it will output to the rich text box that a 
        //path could not be found.
        
        if ( PathFindingType == 0 )//Best First
        {
            BestFirst BestFirstRoute;//Creates a instance of the best first class
            richTextBox1->Text += "Best-First:\n";
            if ( BestFirstRoute.PathFind( Map, richTextBox1 ) )
            {
                pictureBox1->Image = Map.CreateGrid(); 
            }
            else 
            {
                richTextBox1->Text += "\nCould Not find a path!";
            }
            BestFirstRoute.~BestFirst();
            groupBox4->Enabled = false;
        }
        else if ( PathFindingType == 1 )//Dijkstra's
        {
            Dijkstra DijkstraRoute;//Creates a instance of the Dijkstra's class
            richTextBox1->Text += "Dijkstra's:\n";
            if ( DijkstraRoute.PathFind( Map, richTextBox1 ) )
            {
                pictureBox1->Image = Map.CreateGrid(); 
            }
            else 
            {
                richTextBox1->Text += "\nCould Not find a path!";
            }
            DijkstraRoute.~Dijkstra();
            groupBox4->Enabled = false;
        }
        else if ( PathFindingType == 2 )//A*
        {
            AStar AStarRoute;//Creates a instance of the AStar class
            richTextBox1->Text += "A*:\n";
            if ( AStarRoute.PathFind( Map, richTextBox1 ) )
            {
                pictureBox1->Image = Map.CreateGrid(); 
            }
            else 
            {
                richTextBox1->Text += "\nCould Not find a path!";
            }
            AStarRoute.~AStar();
            groupBox4->Enabled = false;
        }

    }
    private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) 
    {
        //Makes picturebox1 blank, clears the rich text box and sets the user back to start.
        pictureBox1->Image = Map.CreateBlank();
        Map.ClearPathArray();
        groupBox1->Enabled = true;
        groupBox2->Enabled = false;
        groupBox4->Enabled = false;
        richTextBox1->Clear();
    }
    private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) 
    {
      //Opens a save file dilog box and lets the user save the output file, a default name is provided
      //so the user can save quickly. 
      Stream^ myStream;
      saveFileDialog1->Title = "Save OutPut File";
      saveFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
      saveFileDialog1->FileName = "output.txt";
      saveFileDialog1->FilterIndex = 1;
      saveFileDialog1->RestoreDirectory = true;
      if ( saveFileDialog1->ShowDialog() == ::DialogResult::OK )
      {
         if ( (myStream = saveFileDialog1->OpenFile()) != nullptr )
         {
           richTextBox1->SaveFile( myStream, RichTextBoxStreamType::PlainText );
           myStream->Close();
         }
      }
    }



};
}

