#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define maxn 30
#define maxm 40
int map[maxn][maxm];
void get_map(){
	int i,j; 
	for(i=0;i<maxn;i++){
		for(j=0;j<maxm;j++){
			scanf("%d",&map[i][j]);
		}
	}
}
int pointvalue(int x,int y){//�õ������е���Ԫ�ص�ֵ��������ֵ 
    int value=0;
	if(!(x>=0&&x<maxn&&y>=0&&y<maxm)||map[x][y]==2017202084) 
	    value=6;
	else if(!(x>=5&&x<=20&&y>=5&&y<=35)&&(map[x][y]==0))//��Χ��ͬ���ո��ֵҲ��ͬ 
	    value=3;
	else if(x>=5&&x<=20&&y>=5&&y<=35&&(map[x][y]==0))//�м�ո�ֵ��С�Դ˾����������������м��� 
	    value=2;
	else if(map[x][y]/2000000000==1&&map[x][y]!=2017202084)
	    value=2000000000;
	else value=map[x][y];
	return value;
}
struct point{ 
	int x,y;
};
int maxvalue(int a[4]){//����һ������Ϊ4һά�м�ֵ��ߵģ�ֵ��С�ģ����� 
	int i;
	int mini=2100000000;
	for(i=0;i<4;i++){
		if(a[i]<mini)//��Ϊʳ���ֵΪ��������ԽС��ֵԽ�� 
		mini=a[i];
	}
	return mini;
}
int dangerous(int a[4]){//�ж��Ƿ��ڵݹ�·;�д��ڱ���ߵ����� 
	int i;
	int danger=-100;
	for(i=0;i<4;i++){
		if(a[i]>danger)
		danger=a[i];
	}
	return danger;
}
int diretotalvalue(int x,int y){//�õ�ĳһ����һ����Χ�����������ʳ��ļ�ֵ�Ͳ��������� 
    int i,j,dire;
	int totalvalue[4]={0};
    for(dire=0;dire<4;dire++){
    	if(dire==0){
		    for(i=x-5;i<=x+5;i++){
		        for(j=y-10;j<=y;j++){//����Χ 
		    	    if(pointvalue(i,j)<0)
				        totalvalue[0]-=pointvalue(i,j);//�ۼ� 
		        }
	        }
	    }
	    else if(dire==1){
		    for(i=x-10;i<=x;i++){
		        for(j=y-5;j<y+5;j++){
		    	    if(pointvalue(i,j)<0)
			            totalvalue[1]-=pointvalue(i,j);
		        }
	        }
	    }
    	else if(dire==2){
	    	for(i=x-5;i<=x+5;i++){
		        for(j=y;j<=y+10;j++){
		        	if(pointvalue(i,j)<0)
			            totalvalue[2]-=pointvalue(i,j);
		        }
	        }
    	}
	    else if(dire==3){
	    	for(i=x;i<=x+10;i++){
		        for(j=y-5;j<y+5;j++){
		        	if(pointvalue(i,j)<0)
			            totalvalue[3]-=pointvalue(i,j);
		        }
	        }
	    }
	}
	int maxvalue=0,choosedire=0;
	for(dire=0;dire<4;dire++){
		if(maxvalue>totalvalue[dire]){
			maxvalue=totalvalue[dire];
			choosedire=dire;//ѡ���ֵ���ķ��� 
		}
	}
	return choosedire;
}
int nearvalue(int x,int y){//�õ�ͷ�������ļ�ֵ 
	int i,j;
	int totalvalue=0;
	for(i=x-3;i<=x+3;i++){
		for(j=y-3;j<=y+3;j++){
			if(i!=x&&j!=y)
			if(pointvalue(i,j)<0)
			    totalvalue++;
		}
	}
	return totalvalue;
}
struct point nearsearch(int x,int y,int range){//ͨ���Ե��㸽��ʳ��ݹ������������Ŀ�겢��������� 
	int value=0;
	struct point goal;
	int i,j,k,l,n;
	for(i=x-range;i<=x+range;i++){
		for(j=y-range;j<=y+range;j++){
			if(i>x-range&&i<x+range&&j>y-range&&j<y+range)
		       continue;
			if(pointvalue(i,j)<value){
		    	value=pointvalue(i,j);
			    goal.x=i;
			    goal.y=j;
		    }
		}
	}
	if(value>=0){
		return nearsearch(x,y,range+1);//���û���ҵ������ʳ���򽫷�Χ����������� 
	}
	else return goal;//����ҵ�ʳ��ֱ�ӷ���Ŀ��� 
}
int dire_recursion(int x,int y,int deep,int wide){//�ݹ�õ���һ����ĳһ����ļ�ֵ 
	//deep��wide�ֱ����������Ⱥ͹�� 
	int i;
    int score[4];
    int _score=0;
    if(pointvalue(x,y)==2000000000)//�����⵽�ߵ����� 
        return 2000000000;//����һ���޴����ֵ 
    if(deep>=6||wide>=10)//�ݹ�����deep�㣬���wide��
        return pointvalue(x,y);
	for(i=0;i<4;i++){
		if(i==0){
		    _score=pointvalue(x,y);
			if(_score>=2)//�������������ʳ����deep&wideͬʱ��һ�����������ֻ��wide��һ��deep����һ 
			score[i]=_score+dire_recursion(x,y-1,deep,wide+1);//���������������·���Ͽո�϶���ݹ�������� 
			else score[i]=_score+dire_recursion(x,y-1,deep+1,wide+1);//���ʳ��϶���ݹ�������� 
		}
		if(i==1){
			_score=pointvalue(x,y);
			if(_score>=2)
			score[i]=_score+dire_recursion(x-1,y,deep,wide+1);
			else score[i]=_score+dire_recursion(x-1,y,deep+1,wide+1);
		}
		if(i==2){
			_score=pointvalue(x,y);
			if(_score>=2)
			score[i]=_score+dire_recursion(x,y+1,deep,wide+1);
			else score[i]=_score+dire_recursion(x,y+1,deep+1,wide+1);
		}
		if(i==3){
			_score=pointvalue(x,y);
			if(_score>=2)
			score[i]=_score+dire_recursion(x+1,y,deep,wide+1);
			else score[i]=_score+dire_recursion(x+1,y,deep+1,wide+1);
		}
	}
	if(dangerous(score)>=1000000)//�������ֵ���о޴����������Ϊ������������ 
	    return dangerous(score);
	return maxvalue(score);//���ص�ǰѭ���з�ֵ����һ������ķ�ֵ 
}
int isdanger(int px,int py){//�ж��ҵ����Ƿ�Ҫ��ײ 
	int i,j;
	for(i=-1;i<=1;i++){
		for(j=-1;j<=1;j++){
			if(i!=0&&j!=0)
			if(map[px+i][py+j]!=2017202084&&map[px+i][py+j]/2000000000==1)
			    return 1;
		}
	}
	return 0;
}
int checkhead(int px,int py){//����ҵ���ͷ�����ޱ����ͷ���߼��ϼ򵥵ģ� 
	int i,j;
	for(i=-1;i<=1;i++){
		for(j=-1;j<=1;j++){
			if(((map[px+i][py+j]/70000==1&&map[px+i][py+j]/10!=7084))){
				if(map[px][py]%10!=map[px+i][py+j]%10)
				return 1;
			}
		} 
	}
	return 0;
}
int attackhead(int px,int py){ //�����ж�������ͷ�ĺ��� ���߼��ϸ��ӵģ� 
	int myDire=map[px][py]%10;
	if(myDire==0&&((map[px][py-2]/70000==1&&map[px][py-2]%10==2)))
		return 1;
	if(myDire==1&&((map[px-2][py]/70000==1&&map[px-2][py]%10==3)))
		return 1;
	if(myDire==2&&((map[px][py+2]/70000==1&&map[px][py+2]%10==0)))
		return 1;
	if(myDire==3&&((map[px+2][py]/70000==1&&map[px+2][py]%10==1)))
		return 1;
		
	if(myDire==0&&((map[px+1][py-1]/70000==1&&map[px+1][py-1]%10==1)))
	    return 1;
	if(myDire==0&&((map[px-1][py-1]/70000==1&&map[px-1][py-1]%10==3)))
	    return 1;
	if(myDire==1&&((map[px-1][py-1]/70000==1&&map[px-1][py-1]%10==2)))
	    return 1;
	if(myDire==1&&((map[px-1][py+1]/70000==1&&map[px-1][py+1]%10==0)))
	    return 1;
	if(myDire==2&&((map[px+1][py+1]/70000==1&&map[px+1][py+1]%10==1)))
	    return 1;
	if(myDire==2&&((map[px-1][py+1]/70000==1&&map[px-1][py+1]%10==3)))
	    return 1;
	if(myDire==3&&((map[px+1][py-1]/70000==1&&map[px+1][py-1]%10==2)))
	    return 1;
	if(myDire==3&&((map[px+1][py+1]/70000==1&&map[px+1][py+1]%10==0)))
	    return 1;
	if(map[px][py]/70000==1&&map[px][py]/10!=7084)
		return 1;
	return 0;
}
struct point head(int px,int py){//�ԶԷ���ͷ����һ���������ж���Ԥ�в����ضԷ��Ŀ��ܵ���һ���ĵ� 
	int i,j;
	int hx,hy,hdire;
	for(i=-1;i<=1;i++){
		for(j=-1;j<=1;j++){
			if(((map[px+i][py+j]/70000==1&&map[px+i][py+j]/10!=7084))){
				hx=px+i;
				hy=py+j;
				hdire=map[px+i][py+j]%10;
			}
		} 
	}
	int changedire=0;
	//��̰���㷨��Ԥ�ж��� 
	struct point p1;
	if(hx<nearsearch(hx,hy,1).x){ 
		changedire=3;
		p1.x=hx+1;
		p1.y=hy; 
	}
	if(hx>nearsearch(hx,hy,1).x){
		changedire=1;
		p1.x=hx-1;
		p1.y=hy; 
	}
    if(hy<nearsearch(hx,hy,1).y){
    	changedire=2;
    	p1.x=hx;
		p1.y=hy+1; 
	}
    if(hy>nearsearch(hx,hy,1).y){
    	changedire=0;
    	p1.x=hx;
		p1.y=hy-1; 
	}
	return p1;
}
void solve(){
    int px=0,py=0,dire=0,changedire=0;
	int i,j;
	for(i=0;i<maxn;i++){
		for(j=0;j<maxm;j++){
			if(map[i][j]/10==7084)//���ҵ��Լ�����ͷ 
			{
				px=i;
				py=j;
				dire=map[i][j]%10; 
				goto jump;
			}
		}
	}
	jump:changedire=dire;
	if(nearvalue(px,py)>0){
		//ֱ��̰���㷨������������ֲ����Ŷ�ʧȥ������Ƶ���� 
		//���ھֲ�С��Χ����ʳ��ɳ�ʱ���Ա���ݹ鿪�� 
		//ͨ���ж��ҵ���ʳ���λ�ú��Լ���ͷ�����λ������������ 
		if(px<nearsearch(px,py,1).x)changedire=3;
	    if(px>nearsearch(px,py,1).x)changedire=1;
	    if(py<nearsearch(px,py,1).y)changedire=2;
	    if(py>nearsearch(px,py,1).y)changedire=0;
	}
	else{
		int maxi[4]={0};
	    for(i=0;i<4;i++){//�ݹ�����deep�㣬���wide�㣬Ҫ��ֱ��̰��Ч����һЩ����Χ��һ�㣬�ҿ����ҵ�ʳ���ܼ��ĵط� 
		    if(i==0)maxi[0]=dire_recursion(px,py-1,0,0);
		    if(i==1)maxi[1]=dire_recursion(px-1,py,0,0);
		    if(i==2)maxi[2]=dire_recursion(px,py+1,0,0);
		    if(i==3)maxi[3]=dire_recursion(px+1,py,0,0);
	    }
	    int best=maxvalue(maxi); 
	    for(i=0;i<4;i++){
	        if(best==maxi[i])
	        changedire=i;
	    } 
	    //����ݹ鷶Χ����ʵ���Ҳ����ܶ�ʳ���ֱ��������Χ��ȷ������ 
	    if(best>=12)
            changedire=diretotalvalue(px,py);
	} 
	
	
	//�ж��Ƿ�Σ�գ����´������ĸ�������ж�һ�£� 
	if(isdanger(px,py)==1&&dire==0){
		if(nearsearch(px,py,1).x>=px)
		    changedire=3;
		else if(nearsearch(px,py,1).x<px)
		    changedire=1;
	}
    else if(isdanger(px,py)==1&&(dire==1||dire==3)){//�������������߲��ų����� 
	    changedire=2;
	}
	
	if(isdanger(px,py)==1&&dire==1){ 
		if(nearsearch(px,py,1).y>=py)
		    changedire=2;
		else if(nearsearch(px,py,1).y<py)
		    changedire=0;
	}
    else if(isdanger(px,py)==1&&(dire==0||dire==2)){
    	changedire=3;
	}   
	
	if(isdanger(px,py)==1&&dire==2){
		 if(nearsearch(px,py,1).x>=px)
		    changedire=3;
		else if(nearsearch(px,py,1).x<px)
		    changedire=1;
	}
    else if(isdanger(px,py)==1&&(dire==1||dire==3)){
    	changedire=0;
	}   
	
	if(isdanger(px,py)==1&&dire==3){
		if(nearsearch(px,py,1).y>=py)
		    changedire=2;
		else if(nearsearch(px,py,1).y<py)
		    changedire=0;
	}
    else if(isdanger(px,py)==1&&(dire==0||dire==2)){
        changedire=1;
	}   
	
	//��ʼ�жϱ߽� 
	if(dire==0){
		if(py<=0)
		changedire=3;
	}
	if(dire==1){
		if(px<=0)
		changedire=0;
	}
	if(dire==2){
		if(py>=maxm-1)
		changedire=1;
	}
	if(dire==3){
		if(px>=maxn-6)
		changedire=2;
	}
	if((px<=0)&&(dire==1)){
		if(nearsearch(px,py,1).y>=py)changedire=2;
		if(nearsearch(px,py,1).y<py)changedire=0;
	}
	if((px<=0)&&(changedire==1))changedire=3;
	
	if((px>=maxn-6)&&(dire==3)){
		if(nearsearch(px,py,1).y>=py)changedire=2;
		if(nearsearch(px,py,1).y<py)changedire=0;
	}
	if((px>=maxn-6)&&(changedire==3))changedire=1;
	
	if((py<=0)&&(dire==0)){
		if(nearsearch(px,py,1).x>=px)changedire=3;
		if(nearsearch(px,py,1).x<px)changedire=1;
	}
    if((py<=0)&&(changedire==0))changedire=2;
    
    if((py>=maxm-1)&&(dire==2)){
    	if(nearsearch(px,py,1).x>=px)changedire=3;
		if(nearsearch(px,py,1).x<px)changedire=1;
	}
    if((py>=maxm-1)&&(changedire==2))changedire=0;
    
	//�ж��Ƿ�ײͷ����� 
	if(checkhead(px,py)==1||attackhead(px,py)==1){
		if(px<head(px,py).x){//����Ҫ�Եз���ͷ����׷�ٺ�Ԥ�У�����ɱ������ 
			changedire=3;
			changedire+=10;
			if(map[px+1][py]/2000000000==1)
			changedire=0;
		}
	    if(px>head(px,py).x){
	    	changedire=1;
	    	changedire+=10;
	    	if(map[px-1][py]/2000000000==1)
			changedire=2;
		}
	    if(py<head(px,py).y){
	    	changedire=2;
	    	changedire+=10;
	    	if(map[px][py+1]/2000000000==1)
			changedire=3;
		}
	    if(py>head(px,py).y){
	    	changedire=0;
	    	changedire+=10;
	    	if(map[px][py-1]/2000000000==1)
			changedire=1;
		}
	}
	
	//������� 
	printf("%d",changedire);
}
int main(int argc, char *argv[]) {
	get_map();
    solve();
	return 0;
}
