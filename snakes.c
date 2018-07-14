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
int pointvalue(int x,int y){//得到数组中单个元素的值并评估价值 
    int value=0;
	if(!(x>=0&&x<maxn&&y>=0&&y<maxm)||map[x][y]==2017202084) 
	    value=6;
	else if(!(x>=5&&x<=20&&y>=5&&y<=35)&&(map[x][y]==0))//范围不同，空格的值也不同 
	    value=3;
	else if(x>=5&&x<=20&&y>=5&&y<=35&&(map[x][y]==0))//中间空格值更小以此尽量吸引蛇优先往中间走 
	    value=2;
	else if(map[x][y]/2000000000==1&&map[x][y]!=2017202084)
	    value=2000000000;
	else value=map[x][y];
	return value;
}
struct point{ 
	int x,y;
};
int maxvalue(int a[4]){//返回一个长度为4一维中价值最高的（值最小的）数字 
	int i;
	int mini=2100000000;
	for(i=0;i<4;i++){
		if(a[i]<mini)//因为食物的值为负，所以越小价值越高 
		mini=a[i];
	}
	return mini;
}
int dangerous(int a[4]){//判断是否在递归路途中存在别的蛇的身体 
	int i;
	int danger=-100;
	for(i=0;i<4;i++){
		if(a[i]>danger)
		danger=a[i];
	}
	return danger;
}
int diretotalvalue(int x,int y){//得到某一方向一定范围内区域的所有食物的价值和并决定方向 
    int i,j,dire;
	int totalvalue[4]={0};
    for(dire=0;dire<4;dire++){
    	if(dire==0){
		    for(i=x-5;i<=x+5;i++){
		        for(j=y-10;j<=y;j++){//区域范围 
		    	    if(pointvalue(i,j)<0)
				        totalvalue[0]-=pointvalue(i,j);//累加 
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
			choosedire=dire;//选择价值最大的方向 
		}
	}
	return choosedire;
}
int nearvalue(int x,int y){//得到头部附近的价值 
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
struct point nearsearch(int x,int y,int range){//通过对单点附近食物递归搜索找最近的目标并返回坐标点 
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
		return nearsearch(x,y,range+1);//如果没有找到满意的食物则将范围扩大继续搜索 
	}
	else return goal;//如果找到食物直接返回目标点 
}
int dire_recursion(int x,int y,int deep,int wide){//递归得到下一步走某一方向的价值 
	//deep和wide分别代表搜索深度和广度 
	int i;
    int score[4];
    int _score=0;
    if(pointvalue(x,y)==2000000000)//如果检测到蛇的身体 
        return 2000000000;//返回一个巨大的正值 
    if(deep>=6||wide>=10)//递归最少deep层，最多wide层
        return pointvalue(x,y);
	for(i=0;i<4;i++){
		if(i==0){
		    _score=pointvalue(x,y);
			if(_score>=2)//如果搜索到的是食物则deep&wide同时加一，如果不是则只有wide加一，deep不加一 
			score[i]=_score+dire_recursion(x,y-1,deep,wide+1);//这样可以做到如果路径上空格较多则递归层数增加 
			else score[i]=_score+dire_recursion(x,y-1,deep+1,wide+1);//如果食物较多则递归层数较少 
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
	if(dangerous(score)>=1000000)//如果返回值中有巨大的数字则认为出现了蛇身体 
	    return dangerous(score);
	return maxvalue(score);//返回当前循环中分值最大的一个方向的分值 
}
int isdanger(int px,int py){//判断我的蛇是否将要相撞 
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
int checkhead(int px,int py){//检查我的蛇头边有无别的蛇头（逻辑较简单的） 
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
int attackhead(int px,int py){ //辅助判断其他蛇头的函数 （逻辑较复杂的） 
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
struct point head(int px,int py){//对对方蛇头的下一步动作进行短期预判并返回对方的可能的下一步的点 
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
	//用贪心算法简单预判对手 
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
			if(map[i][j]/10==7084)//先找到自己的蛇头 
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
		//直接贪心算法搜索，易陷入局部最优而失去整体局势的情况 
		//但在局部小范围内有食物可吃时可以避免递归开销 
		//通过判断找到的食物的位置和自己蛇头的相对位置来决定方向 
		if(px<nearsearch(px,py,1).x)changedire=3;
	    if(px>nearsearch(px,py,1).x)changedire=1;
	    if(py<nearsearch(px,py,1).y)changedire=2;
	    if(py>nearsearch(px,py,1).y)changedire=0;
	}
	else{
		int maxi[4]={0};
	    for(i=0;i<4;i++){//递归最少deep层，最多wide层，要比直接贪心效果好一些，范围大一点，且可以找到食物密集的地方 
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
	    //如果递归范围不够实在找不到很多食物就直接搜索大范围来确定方向 
	    if(best>=12)
            changedire=diretotalvalue(px,py);
	} 
	
	
	//判断是否危险（以下代码是四个方向各判断一下） 
	if(isdanger(px,py)==1&&dire==0){
		if(nearsearch(px,py,1).x>=px)
		    changedire=3;
		else if(nearsearch(px,py,1).x<px)
		    changedire=1;
	}
    else if(isdanger(px,py)==1&&(dire==1||dire==3)){//尽量不和其他蛇并排长期走 
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
	
	//开始判断边界 
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
    
	//判断是否撞头开尖刺 
	if(checkhead(px,py)==1||attackhead(px,py)==1){
		if(px<head(px,py).x){//这里要对敌方蛇头进行追踪和预判，尽量杀掉对手 
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
	
	//输出方向 
	printf("%d",changedire);
}
int main(int argc, char *argv[]) {
	get_map();
    solve();
	return 0;
}
