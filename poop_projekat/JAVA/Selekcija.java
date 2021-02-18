import java.awt.Rectangle;
import java.util.ArrayList;

public class Selekcija {
ArrayList<Rectangle> okviri=new ArrayList<>();
boolean aktivan=true;
public void dodajOkvir(int x,int y,int w,int h) {
	Rectangle r=new Rectangle(x,y,w,h);
	okviri.add(r);
}
public Rectangle dohvatiOkvir(int i) {
	if(i>=0 && i<okviri.size())
	return okviri.get(i);
	
	return null;
}
public int dohvatiBrojOkvira() {
	return okviri.size();
}
public boolean dohvatiAktivan() {
	return aktivan;
}
public void postaviAktivan(boolean b) {
	aktivan=b;
}
}
