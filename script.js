/*var frozen = document.querySelector('#frozen');
var chimera = document.querySelector('#chimera');
var follow = document.querySelector('#follow');
var sun = document.querySelector('#sun');
var iodine = document.querySelector('#iodine');
var chemist = document.querySelector('#chemist');
var close = document.querySelector('#close');
var paranoia = document.querySelector('#paranoia');
var uncle = document.querySelector('#uncle');
var chemist2023 = document.querySelector('#chemist2023');
var sun2023 = document.querySelector('#sun2023');
var iodine2023 = document.querySelector('#iodine2023');*/
var tracks = document.querySelectorAll('#demo2023 audio');
for (let t of tracks) {
	t.onplay = function() {
		for (let o of tracks) {
			if (o != t)
				o.pause();
		}
	}
}
console.assert(tracks.length == 3);
for (let i = 0; i < tracks.length; ++i) {
	if (i < tracks.length - 1) {
		const nexttrack = tracks[i + 1];
		tracks[i].onended = function() { nexttrack.play(); }
	} else {
		const nexttrack = tracks[i - 2];
		tracks[i].onended = function() { nexttrack.play(); }
	}
}
