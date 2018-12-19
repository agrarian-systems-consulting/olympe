inherited DefProduitFrm: TDefProduitFrm
  Left = 298
  Top = 190
  HelpContext = 380
  Caption = 'DefProduitFrm'
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    inherited BtBnNote: TBitBtn
      Enabled = True
    end
  end
  inherited PanHaut: TPanel
    inherited LabelModifie: TLabel
      Visible = False
    end
    inherited BtBnUnite: TBitBtn
      OnClick = BtBnUniteClick
    end
    inherited BtBnTva: TButton
      OnClick = BtBnTvaClick
    end
  end
end
 try
            {
                List<string> mylist = new List<string>();
                foreach (DataRow row in mproductTable.Rows)
                {
                     if (mylist.Contains(row.Field<string>(fieldDisplay))==false)
                    {
                        mylist.Add(row.Field<string>(fieldDisplay));
                    }
                }
                myCombobox.DataSource = mylist; 
            }
			
 if (myCombobox.Name == comboBoxTVA.Name)
                {
List<string> mylist = new List<string>();
                foreach (DataRow row in mproductTable.Rows)
                {
                     if (mylist.Contains(row.Field<string>(fieldDisplay))==false)
                    {
                        mylist.Add(row.Field<string>(fieldDisplay));
                    }
                    
                }
                myCombobox.DataSource = mylist; 
                }
               else
                {
                    SQlQuery UpdateQuery;
                    String[] reader;
                    string SQLQuery = "SELECT " + fieldName + " FROM SystemeUnite;";
                    UpdateQuery = new SQlQuery(mconnectionstring, SQLQuery);
                    reader = UpdateQuery.RunQueryReader();
                    myCombobox.DataSource = reader;
                }

 if (myCombobox.Name == comboBoxTVA.Name)
                {

                }
               else
                {
                    SQlQuery UpdateQuery;
                    String[] reader;
                    string SQLQuery = "SELECT " + fieldName + " FROM SystemeUnite;";
                    UpdateQuery = new SQlQuery(mconnectionstring, SQLQuery);
                    reader = UpdateQuery.RunQueryReader();
                    myCombobox.DataSource = reader;
                }