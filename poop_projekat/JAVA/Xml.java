import java.awt.Rectangle;
import java.awt.image.BufferedImage;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.soap.Node;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.Attr;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
// Import the File class
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.function.Consumer; 
public class Xml {
     public void napraviKompozitnu(String s[],int[]niz) {
    		try {
    	 DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
         DocumentBuilder dBuilder;
	
			dBuilder = dbFactory.newDocumentBuilder();
		
         Document doc = dBuilder.newDocument();
         
         // root element
         Element rootElement = doc.createElement("KompozitnaFunkcija");
         doc.appendChild(rootElement);
         Element opis = doc.createElement("Opis");
         Attr attr = doc.createAttribute("BrojFunkcija");
         attr.setValue(""+s.length);
         opis.setAttributeNode(attr);
         rootElement.appendChild(opis);
         
    	 for(int i=0;i<s.length;i++) {
    		 Element fun = doc.createElement("fun");
    		 Attr atr=doc.createAttribute("Ime");
    		 Attr atr1=doc.createAttribute("Par");
    		 
    		 int arg=niz[i];
    		String c=s[i];
    		atr1.setValue(""+arg);
    		atr.setValue(c);
    		 
    		
    		 
    		 fun.setAttributeNode(atr);
    		 fun.setAttributeNode(atr1);
    		 rootElement.appendChild(fun);
    		 
    	 }
    	 
    	 TransformerFactory transformerFactory = TransformerFactory.newInstance();
         Transformer transformer = transformerFactory.newTransformer();
         DOMSource source = new DOMSource(doc);
         StreamResult result = new StreamResult(new File("C:\\Users\\PC\\Desktop\\Razmjena\\promjena.xml"));
         transformer.transform(source, result);
         
         // Output to console for testing
         StreamResult consoleResult = new StreamResult(System.out);
         transformer.transform(source, consoleResult);
    		} catch (Exception e) {
    			// TODO Auto-generated catch block
    			e.printStackTrace();
    		}
     }
public static void Ucitaj(String s) {
	try {
		File inputFile = new File(s);
    DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
    DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
    Document doc;
	
		doc = dBuilder.parse(inputFile);
		 doc.getDocumentElement().normalize();
	NodeList Rroot=doc.getElementsByTagName("Opis");
	 org.w3c.dom.Node root = Rroot.item(0);
	// if (root.getNodeType() == Node.ELEMENT_NODE) {
	Element e= (Element)root;
//	 }
	String h=e.getAttribute("Visina");
	String w=e.getAttribute("Sirina");	 
		 NodeList nList = doc.getElementsByTagName("Layer"); 
		 
         for (int temp = 0; temp < nList.getLength(); temp++) {
            org.w3c.dom.Node nNode = nList.item(temp);
            if (nNode.getNodeType() == Node.ELEMENT_NODE) {
                Element eElement = (Element) nNode;
               String s1= eElement.getAttribute("Putanja");
               String ao=eElement.getAttribute("Aktivanoperacije");
               String ap=eElement.getAttribute("Aktivanprikaz");
               String sp=eElement.getAttribute("Providnost");
               BufferedImage b=Xml.ucitajS(s1, Integer.parseInt(w), Integer.parseInt(h));
               Sloj ss=new Sloj(b);
               ss.postaviAktivan(Boolean.parseBoolean(ap));
               ss.postaviUcestvuje(Boolean.parseBoolean(ao));
               ss.postaviProzirnost(Integer.parseInt(sp));
               Slika.dohvatiSliku().dodajSloj(ss);
               
              
            }          
         //   System.out.println("\nCurrent Element :" + nNode.getNodeName());
            
         }
		 
	} catch (SAXException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	} catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	} catch (ParserConfigurationException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
   
}
public static void sacuvaj(String s) {
		Slika slika=Slika.dohvatiSliku();
		try {
	         DocumentBuilderFactory dbFactory =
	         DocumentBuilderFactory.newInstance();
	         DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
	         Document doc = dBuilder.newDocument();
	         
	         // root element
	         Element rootElement = doc.createElement("Slika");
	         doc.appendChild(rootElement);

	         // supercars element
	         Element supercar = doc.createElement("Opis");
	         rootElement.appendChild(supercar);

	         // setting attribute to element
	         Attr attr = doc.createAttribute("BrojSlojeva");
	         attr.setValue(""+slika.dohvatiBrojSlojeva());
	         supercar.setAttributeNode(attr);
	         Attr attr1 = doc.createAttribute("Visina");
	         attr1.setValue(""+slika.dohvatiVisinu());
	         supercar.setAttributeNode(attr1);
	         
	         Attr attr2 = doc.createAttribute("Sirina");
	         attr2.setValue(""+slika.dohvatiSirinu());
	         supercar.setAttributeNode(attr2);
	         
	         for(int i=0;i<slika.dohvatiBrojSlojeva();i++) {
	        	 Element sloj = doc.createElement("Layer");
	        	 String putanja="C:\\Users\\PC\\Desktop\\Razmjena\\"+(i+1)+"layer.txt";
	        	 napraviFajl(slika.dohvatiSloj(i), putanja);
	        	 Attr path= doc.createAttribute("Putanja");
	        	 path.setValue(putanja);
	        	 sloj.setAttributeNode(path);
	        	 
	        	 Attr ap= doc.createAttribute("Aktivanprikaz");
	        	 ap.setValue(""+slika.dohvatiSloj(i).dohvatiUcestvuje());
	        	 sloj.setAttributeNode(ap);
	        	 
	        	 Attr ao= doc.createAttribute("Aktivanoperacije");
	        	 ao.setValue(""+slika.dohvatiSloj(i).dohvatiAktivan());
	        	 sloj.setAttributeNode(ao);
	        	 
	        	 Attr p= doc.createAttribute("Providnost");
	        	 p.setValue(""+slika.dohvatiSloj(i).dohvatiProzirnost());
	        	 sloj.setAttributeNode(p);
	        	 supercar.appendChild(sloj);
	         }

	         
	         
	         
	         
	         
	         /////dodavanje selkekcija
	         Element sel = doc.createElement("OpisSelekcije");
	         rootElement.appendChild(sel);

	         // setting attribute to element
	         Attr selatr = doc.createAttribute("BrojSelekcija");
	         selatr.setValue(""+slika.selekcije.size());
	         sel.setAttributeNode(selatr);
	         
	       /*  for(int i=0;i<slika.selekcije.size();i++) {
	        	
	        	 Element numsel = doc.createElement("Selekcija ");
	        	 
	        	 Attr ime=doc.createAttribute("Ime");
	        	slika.selekcije[i]
	         }*/
	         
	         for(Map.Entry<String, Selekcija> entry : slika.selekcije.entrySet()) {
	        	    String key = entry.getKey();
	        	    Selekcija value = entry.getValue();
	        	    Element numsel = doc.createElement("Selekcija");
	        	    Attr ime=doc.createAttribute("Ime");
		        	ime.setValue(key);
		        	numsel.setAttributeNode(ime);
		        	
		        	Attr br=doc.createAttribute("BrojPravougaonika");
		        	br.setValue(""+value.dohvatiBrojOkvira());
		        	numsel.setAttributeNode(br);
		        	
		        	Attr act=doc.createAttribute("Aktivna");
		        	act.setValue(""+value.dohvatiAktivan());
		        	numsel.setAttributeNode(act);
		        	
		        	
		        	value.okviri.forEach(new Consumer<Rectangle>() {
		                @Override
		                public void accept(Rectangle name) {
		                	Element okvir = doc.createElement("Okvir");
				        	Attr vis=doc.createAttribute("vis");
				        	vis.setValue(""+name.height);
				        	okvir.setAttributeNode(vis);
				        	
				        	Attr sir=doc.createAttribute("sir");
				        	sir.setValue(""+name.width);
				        	okvir.setAttributeNode(sir);
				        	
				        	
				        	Attr x=doc.createAttribute("x");
				        	x.setValue(""+name.y);
				        	okvir.setAttributeNode(x);
				        	
				        	Attr y=doc.createAttribute("y");
				        	y.setValue(""+name.x);
				        	okvir.setAttributeNode(y);
				        	numsel.appendChild(okvir);
		                }
		            });
		        	
	       sel.appendChild(numsel);
	         }
	       
	         // write the content into xml file
	         TransformerFactory transformerFactory = TransformerFactory.newInstance();
	         Transformer transformer = transformerFactory.newTransformer();
	         DOMSource source = new DOMSource(doc);
	         StreamResult result = new StreamResult(new File("C:\\Users\\PC\\Desktop\\Razmjena\\ops.xml"));
	         transformer.transform(source, result);
	         
	         // Output to console for testing
	         StreamResult consoleResult = new StreamResult(System.out);
	         transformer.transform(source, consoleResult);
	      } catch (Exception e) {
	         e.printStackTrace();
	      }
	}
static public BufferedImage ucitajS(String s,int w,int h) {
	try {
	FileReader fr=new FileReader(s);
	BufferedImage bi=new BufferedImage(w, h, BufferedImage.TYPE_INT_RGB);
	 for(int i=0;i<h;i++) {
   	  for(int j=0;j<w;j++)
   	  {
   		String r="",g="",bl="",a=""; 
   	  
   		byte b;
		
			b = (byte) fr.read();
		
   		while(b!=0x2c) {
   			r+=(b-48);
   			b=  (byte) fr.read();
   		}
   		b=  (byte) fr.read();
   		
   		while(b!=0x2c) {
   			g+=(b-48);
   			b=  (byte) fr.read();
   		}
   		b=  (byte) fr.read();
   		while(b!=0x2c) {
   			bl+=(b-48);
   			b=  (byte) fr.read();
   		}
   		b=  (byte) fr.read();
   		while(b!=0x3b) {
   			a+=(b-48);
   			b=  (byte) fr.read();
   		}
   		b=  (byte) fr.read();
   		b=  (byte) fr.read();
   		int r1=Integer.parseInt(r);
   		int g1=Integer.parseInt(g);
   		int bl1=Integer.parseInt(bl);
   		bi.setRGB(j, i, (255<<24)+(r1<<16)+(g1<<8)+bl1);
   		}
   		  
   	  
   	  }
	 return bi;
	 } catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
	
}
static public void napraviFajl(Sloj s,String putanja) {
	 try {
	      FileWriter myWriter = new FileWriter(putanja);
	      for(int i=0;i<Slika.dohvatiSliku().dohvatiVisinu();i++) {
	    	  for(int j=0;j<Slika.dohvatiSliku().dohvatiSirinu();j++)
	    	  {
	    		  if(s.dohvatiSirinu()>j && s.dohvatiVisinu()>i) {
	    		int rgba=s.dohvatiSloj().getRGB(j, i)  ;
	    		int r=(rgba& 0x00ff0000)>>16;
	    		int g=(rgba& 0x0000ff00)>>8;
	    		int b=(rgba& 0x000000ff);
	    		int a=(rgba& 0xff000000)>>>24;
	    		a=(a*100)/255;
	    		myWriter.write(""+r+','+g+','+b+','+a+';'+'\n');
	    	  }
	    		  else myWriter.write(""+0+','+0+','+0+','+0+";\n");
	    			  
	    	  }
	      }
	      myWriter.close();
	    
	    } catch (IOException e) {
	      System.out.println("An error occurred.");
	      e.printStackTrace();
	    }
	
}
	public 	static void main(String args[]) {
	/*Sloj s1=new Sloj("C:\\Users\\PC\\Desktop\\slika.bmp");
	Slika slika=Slika.dohvatiSliku();
	slika.dodajSloj(s1);
	Selekcija s=new Selekcija();
	s.dodajOkvir(10, 10, 20, 20);
	s.dodajOkvir(10, 10, 20, 20);
	s.dodajOkvir(10, 10, 20, 20);
	slika.selekcije.put("lsd", s);
	slika.selekcije.put("lsd2", s);
//napraviFajl(s,"C:\\Users\\PC\\Desktop\\slika.txt");
		sacuvaj("sda");*/
	Ucitaj("C:\\Users\\PC\\Desktop\\Razmjena\\ops.xml");
	}
}
