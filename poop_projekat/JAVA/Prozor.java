

import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Map;
import java.util.function.Consumer;

import org.w3c.dom.Attr;
import org.w3c.dom.Element;

//import domaci1.Layer;

//import domaci1.Layer;
public class Prozor extends Frame implements ActionListener,MouseListener,MouseMotionListener {
int cur=-1;
Prozor p=this;
String s="";
Point start=null;
Checkbox sel=new Checkbox("Selekcije",false);
Label koordinate=new Label("alo");
Slika img=Slika.dohvatiSliku();
	public Prozor() {
		super("POOP projekat");
	
		Panel p=new Panel();
		p.setLayout(new GridLayout(2,1));
	p.add(koordinate);
	p.add(sel);
	add(p,BorderLayout.PAGE_END);
	
	dodajMeni();
	setSize(1000,800);
		
		super.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				dispose();
			}
		});
	super.addMouseListener(this);
	super.addMouseMotionListener(this);
		super.setVisible(true);
		super.setLayout(null);
	}
	
	public void mouseMoved(MouseEvent d) {
		Point pnt=d.getPoint();
		koordinate.setText("x = "+pnt.getX()+" : y = "+pnt.getY());
	}
	public void mouseDragged(MouseEvent d) {
		Point pnt=d.getPoint();
		koordinate.setText("x = "+pnt.getX()+" : y = "+pnt.getY());
		
	}
	
	
	public void paint(Graphics g) {
	
		if(img.dohvatiSloj(cur)!=null)
		g.drawImage(img.dohvatiSloj(cur).dohvatiSloj(), 0, 0, null);
		else if(cur==-2)
		{
			g.drawImage(img.dohvatiCitavuSliku().dohvatiSloj(), 0, 0, null);
		}
			else
			g.drawString("Ne postoji sloj sa tim indeksom", 400, 400);
		
	//	g.drawRect(0, 0, 100, 100);
	}
	
	
	public void mouseClicked(MouseEvent d) {
		System.out.print("Dodatak selekcija");
	}
	public void mouseEntered(MouseEvent d) {
		
		System.out.print("Dodatak selekcija");
	}
	public void mouseExited(MouseEvent d) {
		System.out.print("Dodatak selekcija");
	}
	public void mousePressed(MouseEvent d) {
		start=d.getPoint();
		System.out.print("Dodatak selekcija");
	}
	public void mouseReleased(MouseEvent d1) {
		if((d1.getPoint().getX()!=start.getX() || d1.getPoint().getY()!=start.getY())&&sel.getState()) {
			Point pnt=d1.getPoint();

		Dialog d=new Dialog(this,"Selekcija",true);
		d.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				d.setVisible(false);
			}
			
			
	});
		TextField tf=new TextField();
		Label l=new Label("Unesi ime selekcije");
		Button sav=new Button("Sacuvaj");
		Button exi=new Button("Izadji");
		 int minx=start.x>pnt.x?pnt.x:start.x;
	        int miny=start.y>pnt.y?pnt.y:start.y;
	        int maxx=start.x<pnt.x?pnt.x:start.x;
	        int maxy=start.y<pnt.y?pnt.y:start.y;
        sav.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		
        		if(img.selekcije.get(tf.getText())!=null)
        		{
        			img.selekcije.get(tf.getText()).dodajOkvir(minx,miny, maxx-minx,maxy-miny);
        		}
        		else {
        			System.out.print("Nova");
        			Selekcija seel=new Selekcija();
        			seel.dodajOkvir(minx,miny, maxx-minx,maxy-miny);
        			img.selekcije.put(tf.getText(),seel);
        		}
        		d.setVisible(false);
        	}
        });
        exi.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		
        		d.setVisible(false);
        	}
        });
       
        Label opis=new Label("Od tacke ("+minx+","+miny+") i sirine : "+(maxx-minx)+" visine : "+(maxy-miny));
        d.add(sav,BorderLayout.EAST);
        d.add(exi,BorderLayout.WEST);
        d.add(l,BorderLayout.NORTH);
        d.add(tf,BorderLayout.CENTER);
        d.add(opis,BorderLayout.SOUTH);
        d.setSize(300, 300);
        d.setVisible(true);}
	}
	public void actionPerformed(ActionEvent e) {
		String komanda=e.getActionCommand();
		if(komanda.equals("Dodaj sloj")) {
			Dialog d=new Dialog(this,"Dodaj",true);
			d.addWindowListener(new WindowAdapter() {
				public void windowClosing(WindowEvent e) {
					d.setVisible(false);
				}
			});
			
		TextField tf=new TextField();
		Button b=new Button("Dodaj");
		Label l=new Label();
		b.addActionListener(new ActionListener() {
			
			public void actionPerformed(ActionEvent e) {
			img.dodajSloj(tf.getText());
			l.setText(tf.getText());
			cur=0;
			//d.setVisible(false);
			repaint();
			}
		});
		d.add(l,BorderLayout.CENTER);
		d.add(tf,BorderLayout.NORTH);
		d.add(b,BorderLayout.SOUTH);
		d.setSize(300, 300);
		d.setVisible(true);
	
		
		}
		else if(komanda.equals("Obrisi sloj")) {
			Dialog d=new Dialog(this,"Dodaj",true);
			d.addWindowListener(new WindowAdapter() {
				public void windowClosing(WindowEvent e) {
					d.setVisible(false);
				}
			});
			
		TextField tf=new TextField();
		Button b=new Button("Obrisi");
		
		b.addActionListener(new ActionListener() {
			
			public void actionPerformed(ActionEvent e) {
			img.obrisiSloj(Integer.parseInt(tf.getText()));
			
			cur=0;
			//d.setVisible(false);
			repaint();
			}
		});
		
		d.add(tf,BorderLayout.NORTH);
		d.add(b,BorderLayout.SOUTH);
		d.setSize(300, 300);
		d.setVisible(true);
	
		
		}
		else if(komanda.equals("Promjeni svojstva sloja")) {
			if(img.dohvatiBrojSlojeva()>0) {
			Dialog d=new Dialog(this,"Properties",true);
			d.addWindowListener(new WindowAdapter() {
				public void windowClosing(WindowEvent e) {
					d.setVisible(false);
				}
			});
			Panel glavni=new Panel();
			glavni.setLayout(new GridLayout(5,1));
			
			Panel [] p=new Panel[5];
			for(int i=0;i<3;i++) {
				p[i]=new Panel();
			p[i].setLayout(new GridLayout(1,2));
			}
			for(int i=3;i<5;i++) {
				p[i]=new Panel();
			p[i].setLayout(new GridLayout(1,3));
			}
			
			
			
			
			
		TextField tf=new TextField();
		Label l=new Label("Broj sloja");
		p[0].add(l);
		
		
		Choice c=new Choice();
		for(int i=0;i<img.dohvatiBrojSlojeva();i++)
		c.add(""+i);
		
		p[0].add(c);
		Button b=new Button("Izmjeni");
		
		Label l1=new Label("Visina : "+ img.dohvatiSloj(0).dohvatiVisinu());
		Label l2=new Label("Visina : "+ img.dohvatiSloj(0).dohvatiSirinu());
		p[1].add(l1);
		p[1].add(l2);
		
		Label l3=new Label("Aktivan");
		p[3].add(l3);
		CheckboxGroup g=new CheckboxGroup();
		CheckboxGroup g1=new CheckboxGroup();
		
		final Checkbox a,a1;
		if(img.dohvatiSloj(0).dohvatiAktivan()) {
		a=new Checkbox("Da",g,true);
		a1=new Checkbox("Ne",g,false);
		}
		
		else {
			a=new Checkbox("Da",g,false);
			a1=new Checkbox("Ne",g,true);
		}
		p[3].add(a);
		p[3].add(a1);
		
		
		Label l4=new Label("Ucestvuje");
		
		
		
		final Checkbox  a2,a3;
		if(img.dohvatiSloj(0).dohvatiUcestvuje()) {
		a2=new Checkbox("Da",g1,true);
		a3=new Checkbox("Ne",g1,false);
		}
		
		else {
			a2=new Checkbox("Da",g1,false);
			a3=new Checkbox("Ne",g1,true);
		}
		p[4].add(l4);
		p[4].add(a2);
		p[4].add(a3);
		
		Label l5=new Label("Providnost(%) ");
		p[2].add(l5);
		p[2].add(tf);
		b.addActionListener(new ActionListener() {
			
			public void actionPerformed(ActionEvent e) {
			int sloj=Integer.parseInt(c.getSelectedItem());
			boolean akt=a.getState();
			boolean ucs=a2.getState();
			img.dohvatiSloj(sloj).postaviProzirnost(Integer.parseInt(tf.getText()));
			img.dohvatiSloj(sloj).postaviAktivan(akt);
			img.dohvatiSloj(sloj).postaviUcestvuje(ucs);
			
			d.setVisible(false);
			repaint();
			}
		});
        c.addItemListener(new ItemListener() {
        	@Override
        	public void itemStateChanged(ItemEvent e) {
        		
        		int slo=Integer.parseInt(c.getSelectedItem());
        	l1.setText( "Visina : " + img.dohvatiSloj(slo).dohvatiVisinu() );
        	l2.setText( "Visina : " + img.dohvatiSloj(slo).dohvatiSirinu() );
        	a.setState(false);
        	a1.setState(false);
        	a2.setState(false);
        	a3.setState(false);
        	if(img.dohvatiSloj(slo).dohvatiAktivan())a.setState(true);
        	else a1.setState(true);
        	if(img.dohvatiSloj(slo).dohvatiUcestvuje())a2.setState(true);
        	else a3.setState(true);
        	tf.setText(""+img.dohvatiSloj(slo).dohvatiProzirnost());
        	}
        });
		glavni.add(p[0]);
		glavni.add(p[1]);
		glavni.add(p[3]);
		glavni.add(p[4]);
		glavni.add(p[2]);
		d.add(glavni,BorderLayout.CENTER);
		//d.add(tf,BorderLayout.NORTH);
		d.add(b,BorderLayout.SOUTH);
		d.setSize(300, 300);
		d.setVisible(true);
	
			}
		}
	
		else if(komanda.equals("Selekcije")) {
			if(img.selekcije.size()>0) {
			Dialog d=new Dialog(this,"Selekcija",true);
			d.addWindowListener(new WindowAdapter() {
				public void windowClosing(WindowEvent e) {
					d.setVisible(false);
				}
			});
			
			Choice c=new Choice();
		    c.add("------");
	         for(Map.Entry<String, Selekcija> entry : img.selekcije.entrySet()) {
	        	    String key = entry.getKey();
	        	    Selekcija value = entry.getValue();
	        	    c.add(key);
			
			}
  	Checkbox akt=new Checkbox("Aktvna",false);
  	Button b=new Button("Sacuvaj");
  	Label l=new  Label();
	         c.addItemListener(new ItemListener() {
	         	@Override
	         	public void itemStateChanged(ItemEvent e) {
	         		
	         Selekcija s=img.selekcije.get(c.getSelectedItem());
	         akt.setState(s.dohvatiAktivan());
	         l.setText("");
	     	s.okviri.forEach(new Consumer<Rectangle>() {
                @Override
                public void accept(Rectangle name) {
                	String s=l.getText();
                	s+= "Point : ( "+name.x+","+name.y+") ; h = "+name.height+" w = "+name.width+'\n';
	                 	l.setText(s);
                }
            });
	         		
	         } });
	         
	         
	         b.addActionListener(new ActionListener() {
	 			
	 			public void actionPerformed(ActionEvent e) {
	 				 Selekcija s=img.selekcije.get(c.getSelectedItem());
	 				 s.postaviAktivan(akt.getState());
	 			d.setVisible(false);
	 			repaint();
	 			}
	 		});
	         
	         
	         
	         d.add(c,BorderLayout.NORTH);
	         d.add(akt,BorderLayout.WEST);
	         d.add(l,BorderLayout.CENTER);
	         d.add(b,BorderLayout.SOUTH);
	         d.setSize(300, 300);
	         d.setVisible(true);
			}
		
			
		
		
	}}

//	Sloj l=new Sloj("C:\\Users\\PC\\Desktop\\slika.bmp");
  //  l.dohvatiSloj().createGraphics().drawImage(l.dohvatiSloj(), 51, 51, l.dohvatiSirinu(), l.dohvatiVisinu());
	
	public void dodajMeni() {
	MenuBar trakaMenija=new MenuBar();
	Menu file=new Menu("File");
	Menu ops=new Menu("Operacije");
	Menu show=new Menu("Prikaz");
	Menu lay=new Menu("Rad sa Slojevima");
	MenuItem load=new MenuItem("Ucitaj sliku");
	MenuItem save=new MenuItem("Sacuvaj sliku");
	MenuItem exit=new MenuItem("Izlaz");
	file.add(load);
	file.add(save);
	file.add(exit);
	MenuItem base=new MenuItem("Osnovne");
	MenuItem complex=new MenuItem("Slozene");
	MenuItem composite=new MenuItem("Kompozitne");
	ops.add(base);
	ops.add(complex);
	ops.add(composite);
	MenuItem img=new MenuItem("Prikazi sliku");
	MenuItem layer=new MenuItem("Prikazi sloj");
	show.add(layer);
	show.add(img);
	MenuItem addL=new MenuItem("Dodaj sloj");
	MenuItem delL=new MenuItem("Obrisi sloj");
	MenuItem prop=new MenuItem("Promjeni svojstva sloja");
	MenuItem selek=new MenuItem("Selekcije");
	
	lay.add(addL);
	lay.add(delL);
	lay.add(prop);
	lay.add(selek);
	trakaMenija.add(file);
	trakaMenija.add(show);
	trakaMenija.add(ops);
	trakaMenija.add(lay);
	file.addActionListener(new ActionListener() {public void actionPerformed(ActionEvent e) {
		String komanda=e.getActionCommand();
		if(komanda.equals("Izlaz")) {
		dispose();
		return;
		
		}
		else if(komanda.equals("Ucitaj sliku")) {
			
			Dialog d=new Dialog(p,"Ucitaj",true);
			d.setSize(300, 100);
			TextField t=new TextField();
			Button b=new Button("Load");
			d.add(t,BorderLayout.NORTH );
			d.add(b,BorderLayout.SOUTH );
			b.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					System.out.print(t.getText());
				}
			});
			d.addWindowListener(new WindowAdapter() {
				public void windowClosing(WindowEvent e) {
					d.setVisible(false);
				}
			});
			d.setVisible(true);
		}
		else if(komanda.equals("Sacuvaj sliku")) {
			Dialog d=new Dialog(p,"Sacuvaj",true);
			d.setSize(300, 100);
			TextField t=new TextField();
			Button b=new Button("Save");
			d.add(t,BorderLayout.NORTH );
			d.add(b,BorderLayout.SOUTH );
			b.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					System.out.print(t.getText());
				}
			});
			d.addWindowListener(new WindowAdapter() {
				public void windowClosing(WindowEvent e) {
					d.setVisible(false);
				}
			});
			d.setVisible(true);
			
		}
	}});
	show.addActionListener(new ActionListener() {public void actionPerformed(ActionEvent e) {
		
		String komanda=e.getActionCommand();
		if(komanda.equals("Prikazi sliku")) {

		cur=-2;
		p.repaint();
		}
		else if(komanda.equals("Prikazi sloj")) {
			Dialog d=new Dialog(p,"dijalog",true);
			Button b=new Button("Prikazi");
			TextField t=new TextField();
			Label l=new Label("Unesi redni broj sloja");
			b.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					cur=Integer.parseInt(t.getText());
					p.repaint();
				}
				
			});
			d.add(l,BorderLayout.NORTH);
			d.add(b,BorderLayout.SOUTH);
			d.add(t,BorderLayout.CENTER);
			d.setSize(200, 200);
			d.addWindowListener(new WindowAdapter() {
				public void windowClosing(WindowEvent e) {
					d.setVisible(false);
				}
			});
			d.setVisible(true);
			
		}
	}});
	ops.addActionListener(new ActionListener() {public void actionPerformed(ActionEvent e) {
		String komanda=e.getActionCommand();
		if(komanda.equals("Osnovne")) {
      
			Dialog d=new Dialog(p,"Osnovne",true);
			d.addWindowListener(new WindowAdapter() {
				public void windowClosing(WindowEvent e) {
					d.setVisible(false);
				}
			});
			Panel panel=new Panel();
			panel.setLayout(new GridLayout(2,5));
			CheckboxGroup grupa=new CheckboxGroup();
			Checkbox operacije[]= new Checkbox[10];
			operacije[0]=new Checkbox("Sabiranje",grupa,false);
			operacije[1]=new Checkbox("Mnozenje",grupa,false);
			operacije[2]=new Checkbox("Oduzimanje",grupa,false);
			operacije[3]=new Checkbox("Inverzno oduzimanje",grupa,false);
			operacije[4]=new Checkbox("Dijeljenje",grupa,false);
			operacije[5]=new Checkbox("Inverzno dijeljenje",grupa,false);
			operacije[6]=new Checkbox("Max",grupa,false);
			operacije[7]=new Checkbox("Min",grupa,false);
			operacije[8]=new Checkbox("Log",grupa,false);
			operacije[9]=new Checkbox("Abs",grupa,false);
			TextField par=new TextField("0");
			Button b=new Button("Izvrsi");
			b.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					d.setVisible(false);
					//pozivanje programa
				}
			});
			//d.add(s);
			for(int i=0;i<10;i++)
			panel.add(operacije[i]);
			d.add(panel,BorderLayout.CENTER);
			d.add(par,BorderLayout.NORTH);
			d.add(b,BorderLayout.WEST);
			d.setSize(800, 200);
			d.setVisible(true);
		}
		
	
		else if(komanda.equals("Slozene")) {
		      
			Dialog d=new Dialog(p,"Slozene",true);
			d.addWindowListener(new WindowAdapter() {
				public void windowClosing(WindowEvent e) {
					d.setVisible(false);
				}
			});
			Panel panel=new Panel();
			panel.setLayout(new GridLayout(2,2));
			CheckboxGroup grupa=new CheckboxGroup();
			Checkbox operacije[]= new Checkbox[4];
			operacije[0]=new Checkbox("Medijana",grupa,false);
			operacije[1]=new Checkbox("Crno-Bela slika",grupa,false);
			operacije[2]=new Checkbox("Siva slika",grupa,false);
			operacije[3]=new Checkbox("Inverzna slika",grupa,false);
		
		
			
			Button b=new Button("Izvrsi");
			b.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					d.setVisible(false);
					//pozivanje programa
				}
			});
			//d.add(s);
			for(int i=0;i<4;i++)
			panel.add(operacije[i]);
			d.add(panel,BorderLayout.CENTER);
			
			d.add(b,BorderLayout.WEST);
			d.setSize(800, 200);
			d.setVisible(true);
		}
		
		else if(komanda.equals("Kompozitne")) {
		      
			Dialog d=new Dialog(p,"Kompozitne",true);
			d.addWindowListener(new WindowAdapter() {
				public void windowClosing(WindowEvent e) {
					d.setVisible(false);
				}
			});
			Panel panel=new Panel();
			panel.setLayout(new GridLayout(2,7));
		
			Button operacije[]= new Button[14];
           operacije[0]=new Button("Sabiranje");
           operacije[1]=new Button("Oduzimanje");
           operacije[2]=new Button("Dijeljenje");
           operacije[3]=new Button("Mnozenje");
           operacije[4]=new Button("Inverzno dijeljenje");
           operacije[5]=new Button("Inverzno oduzimanje");
           operacije[6]=new Button("Max");
           operacije[7]=new Button("Min");
           operacije[8]=new Button("Log");
           operacije[9]=new Button("Abs");
           operacije[10]=new Button("Inverzna slika");
           operacije[11]=new Button("Crno-bela slika");
           operacije[12]=new Button("Siva slika");
           operacije[13]=new Button("Medijana");
			TextField tf=new TextField("0");
			Label lab=new Label();

			ArrayList<String> nam=new ArrayList<>();
			ArrayList<Integer> par=new ArrayList<>();
			
			Button b=new Button("Izvrsi");
			b.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					d.setVisible(false);
					lab.setText("");
					String nizs[]=new String[nam.size()];
					int niz[]=new int[par.size()];
					int i=0;
					for(String s:nam) {
						nizs[i++]=s;
					}
					i=0;
					for(Integer s:par) {
						niz[i++]=s;
					}
					Xml c=new Xml();
					c.napraviKompozitnu(nizs, niz);
					c.sacuvaj("C:\\Users\\PC\\Desktop\\Razmjena\\mojform.xml");
					p.pokreni();
					Slika.dohvatiSliku().slojevi.clear();
					Xml.Ucitaj("C:\\Users\\PC\\Desktop\\Razmjena\\ops.xml");
					p.repaint();
					//pozivanje programa
				}
			});
			
			
			for( int i=0;i<14;i++)
			operacije[i].addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					//d.setVisible(false);
				switch (e.getActionCommand()) {
				case "Sabiranje":
					nam.add("Sum");
					par.add(Integer.parseInt(tf.getText()));
					break;
				case "Oduzimanje":
					nam.add("Sub");
					par.add(Integer.parseInt(tf.getText()));
					break;
				case "Dijeljenje":
					nam.add("Div");
					par.add(Integer.parseInt(tf.getText()));
					break;
				case "Inverzno dijeljenje":
					nam.add("Idiv");
					par.add(Integer.parseInt(tf.getText()));
					break;
				case "Inverzno oduzimanje":
					nam.add("Isub");
					par.add(Integer.parseInt(tf.getText()));
					break;
				case "Mnozenje":
					nam.add("Mul");
					par.add(Integer.parseInt(tf.getText()));
					break;
				case "Max":
					nam.add("Max");
					par.add(Integer.parseInt(tf.getText()));
					break;
				case "Min":
					nam.add("Min");
					par.add(Integer.parseInt(tf.getText()));
					break;
				case "Log":
					nam.add("Log");
					par.add(Integer.parseInt(tf.getText()));
					break;
				case "Abs":
					nam.add("Abs");
					par.add(Integer.parseInt(tf.getText()));
					break;
				case "Inverzna slika":
					nam.add("Inv");
					par.add(Integer.parseInt(tf.getText()));
					break;
				case "Crno-bela slika":
					nam.add("Crna");
					par.add(Integer.parseInt(tf.getText()));
					break;
				case "Siva slika":
					nam.add("Siva");
					par.add(Integer.parseInt(tf.getText()));
					break;
				case "Medijana":
					nam.add("Med");
					par.add(Integer.parseInt(tf.getText()));
					break;
					 
				}
				s+=e.getActionCommand()+" ";
					lab.setText(s);
					//pozivanje programa
				}});
			//d.add(s);
			for(int i=0;i<14;i++)
			panel.add(operacije[i]);
			d.add(panel,BorderLayout.CENTER);
	
			
			lab.setText(s);
			d.add(b,BorderLayout.WEST);
			d.add(lab,BorderLayout.NORTH);
			d.add(tf,BorderLayout.SOUTH);
			d.setSize(800, 200);
			d.setVisible(true);
		}
		
	}});
	
	
	
	
	lay.addActionListener(this);
	setMenuBar(trakaMenija);
}
	public void pokreni() {
String file="C:\\Users\\PC\\source\\repos\\Project19\\Debug\\Project19.exe "+"C:\\Users\\PC\\Desktop\\Razmjena\\ops.xml "+
		"C:\\Users\\PC\\Desktop\\Razmjena\\promjena.xml";



try {
	Runtime runtime=Runtime.getRuntime();
	Process proces;
	proces = runtime.exec(file);
	proces.waitFor();
} catch (IOException | InterruptedException e) {
	// TODO Auto-generated catch block
	e.printStackTrace();
}



	}
	public static void main(String [] args) {
	/*UvodniProzor p=new UvodniProzor();
	p.start();
	try {
		p.join();
	} catch (InterruptedException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}*/
		Xml c=new Xml();
		String s[]= {"sum","sub","mul"};
		int n[]= {1,23,56};
		c.napraviKompozitnu(s, n);
		Prozor p1=new Prozor();
		System.out.print("akk");
	}
	
}
