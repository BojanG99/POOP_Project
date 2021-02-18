import java.awt.Frame;
import java.awt.Label;

public class UvodniProzor extends Thread{

	
	public UvodniProzor() {

	}
	@Override
	public void  run() {
		Frame f=new Frame("Uvodni ekran");
		Label l=new Label("Dobro dosli",Label.CENTER);
		
		f.add(l);
		
		f.setSize(400, 500);
		f.setVisible(true);
		try {
			sleep(4000);
			f.dispose();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
