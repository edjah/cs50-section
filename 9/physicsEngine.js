// Small vector library
function Vector(x, y, z) {
    this.x = x === undefined ? 0 : x;
    this.y = y === undefined ? 0 : y;
    this.z = z === undefined ? 0 : z;

    this.add = function(u, c) {
        c = c === undefined ? 1 : c;
        return new Vector(this.x + u.x * c, this.y + u.y * c, this.z + u.z * c);
    }

    this.subtract = function(u, c) {
        c = c === undefined ? 1 : c;
        return new Vector(this.x - u.x * c, this.y - u.y * c, this.z - u.z * c);
    }

    this.magnitude = function() {
        let sum = (this.x * this.x) + (this.y * this.y) + (this.z * this.z);
        return Math.sqrt(sum);
    }

    this.dist = function(u) {
        return this.subtract(u).magnitude();
    }

    this.dot = function(u) {
        return (this.x * u.x) + (this.y * u.y) + (this.z * u.z);
    }

    this.normalize = function() {
        let mag = this.magnitude() || Infinity;
        return new Vector(this.x / mag, this.y / mag, this.z / mag);
    }

    this.mult = function(c) {
        return new Vector(this.x * c, this.y * c, this.z * c);
    }

    this.get = function() {
        return new Vector(this.x, this.y, this.z);
    }

    this.round = function() {
        return new Vector(
            Math.round(this.x * 100) / 100,
            Math.round(this.y * 100) / 100,
            Math.round(this.z * 100) / 100
        );
    }

    this.project = function(u) {
        //Project ONTO u
        return u.mult(this.dot(u) / u.dot(u));
    }
}


// Important global variables for assigning a velocity vector
let p1 = new Vector(0, 0);
let p2 = new Vector(0, 0);
let velocityToAssign = new Vector(0, 0);
let velocityVectorActive = false;


// Other important Global variables
let G = 1;                      // Universal Gravitation Constant
let K = 0;                      // Coulomb's Constant
let simSpeed = 0.25;               // Speed of the simulation
let particleMass = 400;         // Mass of a new particle
let numUniqueParticles = 0;     // Constantly increasing unique number
let targetFrameRate = 6900;       // Target FPS for the animation
let list = [];                  // List of all particles in system


$("#simSpeed").on("input", function(event) {
    simSpeed = $(this).val() / 20;
})


// Functions for handling velocity vector creation
function velocityVector() {
    $("#canvas").mousemove(function(event) {
        if (event.which === 1 && velocityVectorActive) {
            p2.x = event.pageX;
            p2.y = event.pageY;
            velocityToAssign.x = p2.x - p1.x;
            velocityToAssign.y = p2.y - p1.y;
            velocityToAssign = velocityToAssign.mult(1 / 30);
            $("#line").attr({
                "x1": p1.x,
                "y1": p1.y,
                "x2": p2.x,
                "y2": p2.y,
                "display": "inline"
            });
        }
    })
};


$("#canvas").mousedown(function(event) {
    if (event.which === 1) {
        p1.x = event.pageX;
        p1.y = event.pageY;
        velocityVectorActive = true;
        velocityVector();
    }
});


$("#canvas").mouseup(function() {
    if (velocityVectorActive) {
        velocityVectorActive = false;
        $("#line").attr("display", "none");
        createParticle(p1, velocityToAssign, particleMass);
        velocityToAssign = new Vector(0, 0);
        p1 = new Vector(0, 0);
        p2 = new Vector(0, 0);
    }
});



// Object definition for a particle
function Particle(htmlID, px, py, vx, vy, mass) {
    this.htmlID = htmlID;
    this.mass = mass;

    this.position = new Vector(px, py);
    this.velocity = new Vector(vx, vy);
    this.netForce = new Vector(0, 0);
    this.radius = Math.sqrt(this.mass);
    let rgb =[0, 0, 0].map(() => Math.floor(Math.random() * 256));
    this.color = `rgb(${rgb.join(",")})`

    this.update = function() {
        let acceleration = this.netForce.mult(1 / this.mass);
        this.velocity = this.velocity.add(acceleration.mult(simSpeed));
        this.position = this.position.add(this.velocity.mult(simSpeed));
        $(this.htmlID).css({
            'r': this.radius,
            'cx': this.position.x,
            'cy': this.position.y,
            'fill': this.color
        })

    }


};



// construct a new particle
function createParticle(p, v, mass) {
    let newTag = document.createElementNS("http://www.w3.org/2000/svg", 'circle');
    let newTagId = "particle" + numUniqueParticles;
    newTag.setAttribute("id", newTagId);

    $("#canvas").append(newTag);
    let particle = new Particle('#' + newTagId, p.x, p.y, v.x, v.y, mass);

    list.push(particle);
    numUniqueParticles++;

    return particle;
};


// calculate gravitational forces
function calculateForces() {
    for (let i = 0; i < list.length; i++) {
        list[i].netForce = new Vector(0, 0);
    }

    for (let i = 0; i < list.length; i++) {
        for (let j = i + 1; j < list.length; j++) {
            let dist = list[i].position.dist(list[j].position);
            if (dist > list[i].radius + list[j].radius) {
                let forceMag = G * list[i].mass * list[j].mass / (dist * dist);
                let direction = list[j].position.subtract(list[i].position).normalize();
                let fVector = direction.mult(forceMag);
                list[i].netForce = list[i].netForce.add(fVector);
                list[j].netForce = list[j].netForce.subtract(fVector);
            }
        }
    }

};


// detect collisions
function collisionDetection() {
    for (let i = 0; i < list.length; i++) {
        for (let j = i + 1; j < list.length; j++) {
            let dist = list[i].position.dist(list[j].position);
            if (dist < list[i].radius + list[j].radius) {
                let p1 = list[i].velocity.mult(list[i].mass);
                let p2 = list[j].velocity.mult(list[j].mass);

                let x1 = list[i].position.mult(list[i].mass);
                let x2 = list[j].position.mult(list[j].mass);

                list[i].mass += list[j].mass;
                list[i].radius = Math.sqrt(list[i].mass);

                list[i].position = x1.add(x2).mult(1 / list[i].mass);
                list[i].velocity = p1.add(p2).mult(1 / list[i].mass);

                $(list[j].htmlID).remove();

                list.splice(j, 1);
                j -= 1;
            }
        }
    }
}

// Tracking framerate
let fpsCounter = document.getElementById("fpscounter");
let fps = {
    startTime: 0,
    frameNumber: 0,
    getFPS: function() {
        this.frameNumber++;
        let d = new Date().getTime(),
        currentTime = (d - this.startTime) / 1000,
        result = Math.floor(this.frameNumber / currentTime);
        if (currentTime > 1) {
            this.startTime = new Date().getTime();
            this.frameNumber = 0;
        }
        return result;
    }
};


// Calculates forces, collisions, and renders a frame
function drawFrame() {
    calculateForces();
    for (let i = 0; i < list.length; i++) {
        list[i].update();
    }
    collisionDetection();
};

// The actual animation
let animation = setInterval(function() {
    drawFrame();
    fpsCounter.innerHTML = "FPS: " + fps.getFPS();
}, 1000 / targetFrameRate);
