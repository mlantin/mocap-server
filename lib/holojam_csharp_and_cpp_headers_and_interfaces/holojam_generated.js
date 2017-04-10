// automatically generated by the FlatBuffers compiler, do not modify

/**
 * @const
 * @namespace
 */
var Holojam = Holojam || {};

/**
 * @const
 * @namespace
 */
Holojam.Protocol = Holojam.Protocol || {};

/**
 * @enum
 */
Holojam.Protocol.NuggetType = {
  UPDATE: 0,
  EVENT: 1
};

/**
 * @constructor
 */
Holojam.Protocol.Nugget = function() {
  /**
   * @type {flatbuffers.ByteBuffer}
   */
  this.bb = null;

  /**
   * @type {number}
   */
  this.bb_pos = 0;
};

/**
 * @param {number} i
 * @param {flatbuffers.ByteBuffer} bb
 * @returns {Holojam.Protocol.Nugget}
 */
Holojam.Protocol.Nugget.prototype.__init = function(i, bb) {
  this.bb_pos = i;
  this.bb = bb;
  return this;
};

/**
 * @param {flatbuffers.ByteBuffer} bb
 * @param {Holojam.Protocol.Nugget=} obj
 * @returns {Holojam.Protocol.Nugget}
 */
Holojam.Protocol.Nugget.getRootAsNugget = function(bb, obj) {
  return (obj || new Holojam.Protocol.Nugget).__init(bb.readInt32(bb.position()) + bb.position(), bb);
};

/**
 * @param {flatbuffers.Encoding=} optionalEncoding
 * @returns {string|Uint8Array}
 */
Holojam.Protocol.Nugget.prototype.scope = function(optionalEncoding) {
  var offset = this.bb.__offset(this.bb_pos, 4);
  return offset ? this.bb.__string(this.bb_pos + offset, optionalEncoding) : null;
};

/**
 * @param {flatbuffers.Encoding=} optionalEncoding
 * @returns {string|Uint8Array}
 */
Holojam.Protocol.Nugget.prototype.origin = function(optionalEncoding) {
  var offset = this.bb.__offset(this.bb_pos, 6);
  return offset ? this.bb.__string(this.bb_pos + offset, optionalEncoding) : null;
};

/**
 * @returns {Holojam.Protocol.NuggetType}
 */
Holojam.Protocol.Nugget.prototype.type = function() {
  var offset = this.bb.__offset(this.bb_pos, 8);
  return offset ? /** @type {Holojam.Protocol.NuggetType} */ (this.bb.readInt8(this.bb_pos + offset)) : Holojam.Protocol.NuggetType.UPDATE;
};

/**
 * @param {number} index
 * @param {Holojam.Protocol.Flake=} obj
 * @returns {Holojam.Protocol.Flake}
 */
Holojam.Protocol.Nugget.prototype.flakes = function(index, obj) {
  var offset = this.bb.__offset(this.bb_pos, 10);
  return offset ? (obj || new Holojam.Protocol.Flake).__init(this.bb.__indirect(this.bb.__vector(this.bb_pos + offset) + index * 4), this.bb) : null;
};

/**
 * @returns {number}
 */
Holojam.Protocol.Nugget.prototype.flakesLength = function() {
  var offset = this.bb.__offset(this.bb_pos, 10);
  return offset ? this.bb.__vector_len(this.bb_pos + offset) : 0;
};

/**
 * @param {flatbuffers.Builder} builder
 */
Holojam.Protocol.Nugget.startNugget = function(builder) {
  builder.startObject(4);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} scopeOffset
 */
Holojam.Protocol.Nugget.addScope = function(builder, scopeOffset) {
  builder.addFieldOffset(0, scopeOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} originOffset
 */
Holojam.Protocol.Nugget.addOrigin = function(builder, originOffset) {
  builder.addFieldOffset(1, originOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {Holojam.Protocol.NuggetType} type
 */
Holojam.Protocol.Nugget.addType = function(builder, type) {
  builder.addFieldInt8(2, type, Holojam.Protocol.NuggetType.UPDATE);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} flakesOffset
 */
Holojam.Protocol.Nugget.addFlakes = function(builder, flakesOffset) {
  builder.addFieldOffset(3, flakesOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {Array.<flatbuffers.Offset>} data
 * @returns {flatbuffers.Offset}
 */
Holojam.Protocol.Nugget.createFlakesVector = function(builder, data) {
  builder.startVector(4, data.length, 4);
  for (var i = data.length - 1; i >= 0; i--) {
    builder.addOffset(data[i]);
  }
  return builder.endVector();
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {number} numElems
 */
Holojam.Protocol.Nugget.startFlakesVector = function(builder, numElems) {
  builder.startVector(4, numElems, 4);
};

/**
 * @param {flatbuffers.Builder} builder
 * @returns {flatbuffers.Offset}
 */
Holojam.Protocol.Nugget.endNugget = function(builder) {
  var offset = builder.endObject();
  builder.requiredField(offset, 10); // flakes
  return offset;
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} offset
 */
Holojam.Protocol.Nugget.finishNuggetBuffer = function(builder, offset) {
  builder.finish(offset);
};

/**
 * @constructor
 */
Holojam.Protocol.Flake = function() {
  /**
   * @type {flatbuffers.ByteBuffer}
   */
  this.bb = null;

  /**
   * @type {number}
   */
  this.bb_pos = 0;
};

/**
 * @param {number} i
 * @param {flatbuffers.ByteBuffer} bb
 * @returns {Holojam.Protocol.Flake}
 */
Holojam.Protocol.Flake.prototype.__init = function(i, bb) {
  this.bb_pos = i;
  this.bb = bb;
  return this;
};

/**
 * @param {flatbuffers.ByteBuffer} bb
 * @param {Holojam.Protocol.Flake=} obj
 * @returns {Holojam.Protocol.Flake}
 */
Holojam.Protocol.Flake.getRootAsFlake = function(bb, obj) {
  return (obj || new Holojam.Protocol.Flake).__init(bb.readInt32(bb.position()) + bb.position(), bb);
};

/**
 * @param {flatbuffers.Encoding=} optionalEncoding
 * @returns {string|Uint8Array}
 */
Holojam.Protocol.Flake.prototype.label = function(optionalEncoding) {
  var offset = this.bb.__offset(this.bb_pos, 4);
  return offset ? this.bb.__string(this.bb_pos + offset, optionalEncoding) : null;
};

/**
 * @param {number} index
 * @param {Holojam.Protocol.Vector3=} obj
 * @returns {Holojam.Protocol.Vector3}
 */
Holojam.Protocol.Flake.prototype.vector3s = function(index, obj) {
  var offset = this.bb.__offset(this.bb_pos, 6);
  return offset ? (obj || new Holojam.Protocol.Vector3).__init(this.bb.__vector(this.bb_pos + offset) + index * 12, this.bb) : null;
};

/**
 * @returns {number}
 */
Holojam.Protocol.Flake.prototype.vector3sLength = function() {
  var offset = this.bb.__offset(this.bb_pos, 6);
  return offset ? this.bb.__vector_len(this.bb_pos + offset) : 0;
};

/**
 * @param {number} index
 * @param {Holojam.Protocol.Vector4=} obj
 * @returns {Holojam.Protocol.Vector4}
 */
Holojam.Protocol.Flake.prototype.vector4s = function(index, obj) {
  var offset = this.bb.__offset(this.bb_pos, 8);
  return offset ? (obj || new Holojam.Protocol.Vector4).__init(this.bb.__vector(this.bb_pos + offset) + index * 16, this.bb) : null;
};

/**
 * @returns {number}
 */
Holojam.Protocol.Flake.prototype.vector4sLength = function() {
  var offset = this.bb.__offset(this.bb_pos, 8);
  return offset ? this.bb.__vector_len(this.bb_pos + offset) : 0;
};

/**
 * @param {number} index
 * @returns {number}
 */
Holojam.Protocol.Flake.prototype.floats = function(index) {
  var offset = this.bb.__offset(this.bb_pos, 10);
  return offset ? this.bb.readFloat32(this.bb.__vector(this.bb_pos + offset) + index * 4) : 0;
};

/**
 * @returns {number}
 */
Holojam.Protocol.Flake.prototype.floatsLength = function() {
  var offset = this.bb.__offset(this.bb_pos, 10);
  return offset ? this.bb.__vector_len(this.bb_pos + offset) : 0;
};

/**
 * @returns {Float32Array}
 */
Holojam.Protocol.Flake.prototype.floatsArray = function() {
  var offset = this.bb.__offset(this.bb_pos, 10);
  return offset ? new Float32Array(this.bb.bytes().buffer, this.bb.bytes().byteOffset + this.bb.__vector(this.bb_pos + offset), this.bb.__vector_len(this.bb_pos + offset)) : null;
};

/**
 * @param {number} index
 * @returns {number}
 */
Holojam.Protocol.Flake.prototype.ints = function(index) {
  var offset = this.bb.__offset(this.bb_pos, 12);
  return offset ? this.bb.readInt32(this.bb.__vector(this.bb_pos + offset) + index * 4) : 0;
};

/**
 * @returns {number}
 */
Holojam.Protocol.Flake.prototype.intsLength = function() {
  var offset = this.bb.__offset(this.bb_pos, 12);
  return offset ? this.bb.__vector_len(this.bb_pos + offset) : 0;
};

/**
 * @returns {Int32Array}
 */
Holojam.Protocol.Flake.prototype.intsArray = function() {
  var offset = this.bb.__offset(this.bb_pos, 12);
  return offset ? new Int32Array(this.bb.bytes().buffer, this.bb.bytes().byteOffset + this.bb.__vector(this.bb_pos + offset), this.bb.__vector_len(this.bb_pos + offset)) : null;
};

/**
 * @param {number} index
 * @returns {number}
 */
Holojam.Protocol.Flake.prototype.bytes = function(index) {
  var offset = this.bb.__offset(this.bb_pos, 14);
  return offset ? this.bb.readUint8(this.bb.__vector(this.bb_pos + offset) + index) : 0;
};

/**
 * @returns {number}
 */
Holojam.Protocol.Flake.prototype.bytesLength = function() {
  var offset = this.bb.__offset(this.bb_pos, 14);
  return offset ? this.bb.__vector_len(this.bb_pos + offset) : 0;
};

/**
 * @returns {Uint8Array}
 */
Holojam.Protocol.Flake.prototype.bytesArray = function() {
  var offset = this.bb.__offset(this.bb_pos, 14);
  return offset ? new Uint8Array(this.bb.bytes().buffer, this.bb.bytes().byteOffset + this.bb.__vector(this.bb_pos + offset), this.bb.__vector_len(this.bb_pos + offset)) : null;
};

/**
 * @param {flatbuffers.Encoding=} optionalEncoding
 * @returns {string|Uint8Array}
 */
Holojam.Protocol.Flake.prototype.text = function(optionalEncoding) {
  var offset = this.bb.__offset(this.bb_pos, 16);
  return offset ? this.bb.__string(this.bb_pos + offset, optionalEncoding) : null;
};

/**
 * @param {flatbuffers.Builder} builder
 */
Holojam.Protocol.Flake.startFlake = function(builder) {
  builder.startObject(7);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} labelOffset
 */
Holojam.Protocol.Flake.addLabel = function(builder, labelOffset) {
  builder.addFieldOffset(0, labelOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} vector3sOffset
 */
Holojam.Protocol.Flake.addVector3s = function(builder, vector3sOffset) {
  builder.addFieldOffset(1, vector3sOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {number} numElems
 */
Holojam.Protocol.Flake.startVector3sVector = function(builder, numElems) {
  builder.startVector(12, numElems, 4);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} vector4sOffset
 */
Holojam.Protocol.Flake.addVector4s = function(builder, vector4sOffset) {
  builder.addFieldOffset(2, vector4sOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {number} numElems
 */
Holojam.Protocol.Flake.startVector4sVector = function(builder, numElems) {
  builder.startVector(16, numElems, 4);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} floatsOffset
 */
Holojam.Protocol.Flake.addFloats = function(builder, floatsOffset) {
  builder.addFieldOffset(3, floatsOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {Array.<number>} data
 * @returns {flatbuffers.Offset}
 */
Holojam.Protocol.Flake.createFloatsVector = function(builder, data) {
  builder.startVector(4, data.length, 4);
  for (var i = data.length - 1; i >= 0; i--) {
    builder.addFloat32(data[i]);
  }
  return builder.endVector();
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {number} numElems
 */
Holojam.Protocol.Flake.startFloatsVector = function(builder, numElems) {
  builder.startVector(4, numElems, 4);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} intsOffset
 */
Holojam.Protocol.Flake.addInts = function(builder, intsOffset) {
  builder.addFieldOffset(4, intsOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {Array.<number>} data
 * @returns {flatbuffers.Offset}
 */
Holojam.Protocol.Flake.createIntsVector = function(builder, data) {
  builder.startVector(4, data.length, 4);
  for (var i = data.length - 1; i >= 0; i--) {
    builder.addInt32(data[i]);
  }
  return builder.endVector();
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {number} numElems
 */
Holojam.Protocol.Flake.startIntsVector = function(builder, numElems) {
  builder.startVector(4, numElems, 4);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} bytesOffset
 */
Holojam.Protocol.Flake.addBytes = function(builder, bytesOffset) {
  builder.addFieldOffset(5, bytesOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {Array.<number>} data
 * @returns {flatbuffers.Offset}
 */
Holojam.Protocol.Flake.createBytesVector = function(builder, data) {
  builder.startVector(1, data.length, 1);
  for (var i = data.length - 1; i >= 0; i--) {
    builder.addInt8(data[i]);
  }
  return builder.endVector();
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {number} numElems
 */
Holojam.Protocol.Flake.startBytesVector = function(builder, numElems) {
  builder.startVector(1, numElems, 1);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {flatbuffers.Offset} textOffset
 */
Holojam.Protocol.Flake.addText = function(builder, textOffset) {
  builder.addFieldOffset(6, textOffset, 0);
};

/**
 * @param {flatbuffers.Builder} builder
 * @returns {flatbuffers.Offset}
 */
Holojam.Protocol.Flake.endFlake = function(builder) {
  var offset = builder.endObject();
  builder.requiredField(offset, 4); // label
  return offset;
};

/**
 * @constructor
 */
Holojam.Protocol.Vector3 = function() {
  /**
   * @type {flatbuffers.ByteBuffer}
   */
  this.bb = null;

  /**
   * @type {number}
   */
  this.bb_pos = 0;
};

/**
 * @param {number} i
 * @param {flatbuffers.ByteBuffer} bb
 * @returns {Holojam.Protocol.Vector3}
 */
Holojam.Protocol.Vector3.prototype.__init = function(i, bb) {
  this.bb_pos = i;
  this.bb = bb;
  return this;
};

/**
 * @returns {number}
 */
Holojam.Protocol.Vector3.prototype.x = function() {
  return this.bb.readFloat32(this.bb_pos);
};

/**
 * @returns {number}
 */
Holojam.Protocol.Vector3.prototype.y = function() {
  return this.bb.readFloat32(this.bb_pos + 4);
};

/**
 * @returns {number}
 */
Holojam.Protocol.Vector3.prototype.z = function() {
  return this.bb.readFloat32(this.bb_pos + 8);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {number} x
 * @param {number} y
 * @param {number} z
 * @returns {flatbuffers.Offset}
 */
Holojam.Protocol.Vector3.createVector3 = function(builder, x, y, z) {
  builder.prep(4, 12);
  builder.writeFloat32(z);
  builder.writeFloat32(y);
  builder.writeFloat32(x);
  return builder.offset();
};

/**
 * @constructor
 */
Holojam.Protocol.Vector4 = function() {
  /**
   * @type {flatbuffers.ByteBuffer}
   */
  this.bb = null;

  /**
   * @type {number}
   */
  this.bb_pos = 0;
};

/**
 * @param {number} i
 * @param {flatbuffers.ByteBuffer} bb
 * @returns {Holojam.Protocol.Vector4}
 */
Holojam.Protocol.Vector4.prototype.__init = function(i, bb) {
  this.bb_pos = i;
  this.bb = bb;
  return this;
};

/**
 * @returns {number}
 */
Holojam.Protocol.Vector4.prototype.x = function() {
  return this.bb.readFloat32(this.bb_pos);
};

/**
 * @returns {number}
 */
Holojam.Protocol.Vector4.prototype.y = function() {
  return this.bb.readFloat32(this.bb_pos + 4);
};

/**
 * @returns {number}
 */
Holojam.Protocol.Vector4.prototype.z = function() {
  return this.bb.readFloat32(this.bb_pos + 8);
};

/**
 * @returns {number}
 */
Holojam.Protocol.Vector4.prototype.w = function() {
  return this.bb.readFloat32(this.bb_pos + 12);
};

/**
 * @param {flatbuffers.Builder} builder
 * @param {number} x
 * @param {number} y
 * @param {number} z
 * @param {number} w
 * @returns {flatbuffers.Offset}
 */
Holojam.Protocol.Vector4.createVector4 = function(builder, x, y, z, w) {
  builder.prep(4, 16);
  builder.writeFloat32(w);
  builder.writeFloat32(z);
  builder.writeFloat32(y);
  builder.writeFloat32(x);
  return builder.offset();
};

// Exports for Node.js and RequireJS
this.Holojam = Holojam;