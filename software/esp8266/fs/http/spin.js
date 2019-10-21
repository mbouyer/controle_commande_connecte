var looper;
var degrees = 0;
var anim = 0;
function rotateAnimation(el,speed){
	var elem = document.getElementById(el);
	looper = setTimeout('rotateAnimation(\''+el+'\','+speed+')',speed);
	if (anim) {
		if(navigator.userAgent.match("Chrome")){
			elem.style.WebkitTransform = "rotate("+degrees+"deg)";
		} else if(navigator.userAgent.match("Firefox")){
			elem.style.MozTransform = "rotate("+degrees+"deg)";
		} else if(navigator.userAgent.match("MSIE")){
			elem.style.msTransform = "rotate("+degrees+"deg)";
		} else if(navigator.userAgent.match("Opera")){
			elem.style.OTransform = "rotate("+degrees+"deg)";
		} else {
			elem.style.transform = "rotate("+degrees+"deg)";
		}
		degrees+=5;
		if(degrees > 359){
			degrees = 1;
		}
	}
}
function rotateActive(_anim) {
	anim = _anim;
}
